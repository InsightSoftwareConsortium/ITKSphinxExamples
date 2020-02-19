/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

// The program progresses as follows:
// 1) Read the input series
// 2) Resample the series according to the user specified x-y-z
//    spacing.
// 3) Create a MetaDataDictionary for each slice.
// 4) Shift data to undo the effect of a rescale intercept by the
//    DICOM reader (only for ITK < 4.6)
// 5) Write the new DICOM series
//

#include "itkVersion.h"

#include "itkImage.h"
#include "itkMinimumMaximumImageFilter.h"

#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include "itkNumericSeriesFileNames.h"

#include "itkImageSeriesReader.h"
#include "itkImageSeriesWriter.h"

#include "itkResampleImageFilter.h"

#if ((ITK_VERSION_MAJOR == 4) && (ITK_VERSION_MINOR < 6))
#  include "itkShiftScaleImageFilter.h"
#endif

#include "itkIdentityTransform.h"
#include "itkLinearInterpolateImageFunction.h"

#include <itksys/SystemTools.hxx>

#if ITK_VERSION_MAJOR >= 4
#  include "gdcmUIDGenerator.h"
#else
#  include "gdcm/src/gdcmFile.h"
#  include "gdcm/src/gdcmUtil.h"
#endif

#include <string>
#include <sstream>

static void
CopyDictionary(itk::MetaDataDictionary & fromDict, itk::MetaDataDictionary & toDict);


int
main(int argc, char * argv[])
{
  // Validate input parameters
  if (argc < 4)
  {
    std::cerr << "Usage: " << argv[0] << " InputDicomDirectory OutputDicomDirectory spacing_x spacing_y spacing_z"
              << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int InputDimension = 3;
  constexpr unsigned int OutputDimension = 2;

  using PixelType = signed short;

  using InputImageType = itk::Image<PixelType, InputDimension>;
  using OutputImageType = itk::Image<PixelType, OutputDimension>;
  using ReaderType = itk::ImageSeriesReader<InputImageType>;
  using ImageIOType = itk::GDCMImageIO;
  using InputNamesGeneratorType = itk::GDCMSeriesFileNames;
  using OutputNamesGeneratorType = itk::NumericSeriesFileNames;
  using TransformType = itk::IdentityTransform<double, InputDimension>;
  using InterpolatorType = itk::LinearInterpolateImageFunction<InputImageType, double>;
  using ResampleFilterType = itk::ResampleImageFilter<InputImageType, InputImageType>;
#if ((ITK_VERSION_MAJOR == 4) && (ITK_VERSION_MINOR < 6))
  using ShiftScaleType = itk::ShiftScaleImageFilter<InputImageType, InputImageType>;
#endif
  using SeriesWriterType = itk::ImageSeriesWriter<InputImageType, OutputImageType>;

  ////////////////////////////////////////////////
  // 1) Read the input series

  ImageIOType::Pointer             gdcmIO = ImageIOType::New();
  InputNamesGeneratorType::Pointer inputNames = InputNamesGeneratorType::New();
  inputNames->SetInputDirectory(argv[1]);

  const ReaderType::FileNamesContainer & filenames = inputNames->GetInputFileNames();

  ReaderType::Pointer reader = ReaderType::New();

  reader->SetImageIO(gdcmIO);
  reader->SetFileNames(filenames);
  try
  {
    reader->Update();
  }
  catch (itk::ExceptionObject & excp)
  {
    std::cerr << "Exception thrown while reading the series" << std::endl;
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
  }

  ////////////////////////////////////////////////
  // 2) Resample the series
  InterpolatorType::Pointer interpolator = InterpolatorType::New();

  TransformType::Pointer transform = TransformType::New();
  transform->SetIdentity();

  const InputImageType::SpacingType & inputSpacing = reader->GetOutput()->GetSpacing();
  const InputImageType::RegionType &  inputRegion = reader->GetOutput()->GetLargestPossibleRegion();
  const InputImageType::SizeType &    inputSize = inputRegion.GetSize();

  std::cout << "The input series in directory " << argv[1] << " has " << filenames.size() << " files with spacing "
            << inputSpacing << std::endl;

  // Compute the size of the output. The user specifies a spacing on
  // the command line. If the spacing is 0, the input spacing will be
  // used. The size (# of pixels) in the output is recomputed using
  // the ratio of the input and output sizes.
  InputImageType::SpacingType outputSpacing;
  outputSpacing[0] = std::stod(argv[3]);
  outputSpacing[1] = std::stod(argv[4]);
  outputSpacing[2] = std::stod(argv[5]);

  bool changeInSpacing = false;
  for (unsigned int i = 0; i < 3; i++)
  {
    if (outputSpacing[i] == 0.0)
    {
      outputSpacing[i] = inputSpacing[i];
    }
    else
    {
      changeInSpacing = true;
    }
  }
  InputImageType::SizeType outputSize;
  using SizeValueType = InputImageType::SizeType::SizeValueType;
  outputSize[0] = static_cast<SizeValueType>(inputSize[0] * inputSpacing[0] / outputSpacing[0] + .5);
  outputSize[1] = static_cast<SizeValueType>(inputSize[1] * inputSpacing[1] / outputSpacing[1] + .5);
  outputSize[2] = static_cast<SizeValueType>(inputSize[2] * inputSpacing[2] / outputSpacing[2] + .5);

  ResampleFilterType::Pointer resampler = ResampleFilterType::New();
  resampler->SetInput(reader->GetOutput());
  resampler->SetTransform(transform);
  resampler->SetInterpolator(interpolator);
  resampler->SetOutputOrigin(reader->GetOutput()->GetOrigin());
  resampler->SetOutputSpacing(outputSpacing);
  resampler->SetOutputDirection(reader->GetOutput()->GetDirection());
  resampler->SetSize(outputSize);
  resampler->Update();


  ////////////////////////////////////////////////
  // 3) Create a MetaDataDictionary for each slice.

  // Copy the dictionary from the first image and override slice
  // specific fields
  ReaderType::DictionaryRawPointer inputDict = (*(reader->GetMetaDataDictionaryArray()))[0];
  ReaderType::DictionaryArrayType  outputArray;

  // To keep the new series in the same study as the original we need
  // to keep the same study UID. But we need new series and frame of
  // reference UID's.
#if ITK_VERSION_MAJOR >= 4
  gdcm::UIDGenerator suid;
  std::string        seriesUID = suid.Generate();
  gdcm::UIDGenerator fuid;
  std::string        frameOfReferenceUID = fuid.Generate();
#else
  std::string seriesUID = gdcm::Util::CreateUniqueUID(gdcmIO->GetUIDPrefix());
  std::string frameOfReferenceUID = gdcm::Util::CreateUniqueUID(gdcmIO->GetUIDPrefix());
#endif
  std::string studyUID;
  std::string sopClassUID;
  itk::ExposeMetaData<std::string>(*inputDict, "0020|000d", studyUID);
  itk::ExposeMetaData<std::string>(*inputDict, "0008|0016", sopClassUID);
  gdcmIO->KeepOriginalUIDOn();

  for (unsigned int f = 0; f < outputSize[2]; f++)
  {
    // Create a new dictionary for this slice
    auto dict = new ReaderType::DictionaryType;

    // Copy the dictionary from the first slice
    CopyDictionary(*inputDict, *dict);

    // Set the UID's for the study, series, SOP  and frame of reference
    itk::EncapsulateMetaData<std::string>(*dict, "0020|000d", studyUID);
    itk::EncapsulateMetaData<std::string>(*dict, "0020|000e", seriesUID);
    itk::EncapsulateMetaData<std::string>(*dict, "0020|0052", frameOfReferenceUID);

#if ITK_VERSION_MAJOR >= 4
    gdcm::UIDGenerator sopuid;
    std::string        sopInstanceUID = sopuid.Generate();
#else
    std::string sopInstanceUID = gdcm::Util::CreateUniqueUID(gdcmIO->GetUIDPrefix());
#endif
    itk::EncapsulateMetaData<std::string>(*dict, "0008|0018", sopInstanceUID);
    itk::EncapsulateMetaData<std::string>(*dict, "0002|0003", sopInstanceUID);

    // Change fields that are slice specific
    std::ostringstream value;
    value.str("");
    value << f + 1;

    // Image Number
    itk::EncapsulateMetaData<std::string>(*dict, "0020|0013", value.str());

    // Series Description - Append new description to current series
    // description
    std::string oldSeriesDesc;
    itk::ExposeMetaData<std::string>(*inputDict, "0008|103e", oldSeriesDesc);

    value.str("");
    value << oldSeriesDesc << ": Resampled with pixel spacing " << outputSpacing[0] << ", " << outputSpacing[1] << ", "
          << outputSpacing[2];
    // This is an long string and there is a 64 character limit in the
    // standard
    unsigned lengthDesc = value.str().length();

    std::string seriesDesc(value.str(), 0, lengthDesc > 64 ? 64 : lengthDesc);
    itk::EncapsulateMetaData<std::string>(*dict, "0008|103e", seriesDesc);

    // Series Number
    value.str("");
    value << 1001;
    itk::EncapsulateMetaData<std::string>(*dict, "0020|0011", value.str());

    // Derivation Description - How this image was derived
    value.str("");
    for (int i = 0; i < argc; i++)
    {
      value << argv[i] << " ";
    }
    value << ": " << ITK_SOURCE_VERSION;

    lengthDesc = value.str().length();
    std::string derivationDesc(value.str(), 0, lengthDesc > 1024 ? 1024 : lengthDesc);
    itk::EncapsulateMetaData<std::string>(*dict, "0008|2111", derivationDesc);

    // Image Position Patient: This is calculated by computing the
    // physical coordinate of the first pixel in each slice.
    InputImageType::PointType position;
    InputImageType::IndexType index;
    index[0] = 0;
    index[1] = 0;
    index[2] = f;
    resampler->GetOutput()->TransformIndexToPhysicalPoint(index, position);

    value.str("");
    value << position[0] << "\\" << position[1] << "\\" << position[2];
    itk::EncapsulateMetaData<std::string>(*dict, "0020|0032", value.str());
    // Slice Location: For now, we store the z component of the Image
    // Position Patient.
    value.str("");
    value << position[2];
    itk::EncapsulateMetaData<std::string>(*dict, "0020|1041", value.str());

    if (changeInSpacing)
    {
      // Slice Thickness: For now, we store the z spacing
      value.str("");
      value << outputSpacing[2];
      itk::EncapsulateMetaData<std::string>(*dict, "0018|0050", value.str());
      // Spacing Between Slices
      itk::EncapsulateMetaData<std::string>(*dict, "0018|0088", value.str());
    }

    // Save the dictionary
    outputArray.push_back(dict);
  }

#if ((ITK_VERSION_MAJOR == 4) && (ITK_VERSION_MINOR < 6))
  ////////////////////////////////////////////////
  // 4) Shift data to undo the effect of a rescale intercept by the
  //    DICOM reader
  std::string interceptTag("0028|1052");
  using MetaDataStringType = itk::MetaDataObject<std::string>;
  itk::MetaDataObjectBase::Pointer entry = (*inputDict)[interceptTag];

  MetaDataStringType::ConstPointer interceptValue = dynamic_cast<const MetaDataStringType *>(entry.GetPointer());

  int interceptShift = 0;
  if (interceptValue)
  {
    std::string tagValue = interceptValue->GetMetaDataObjectValue();
    interceptShift = -atoi(tagValue.c_str());
  }

  ShiftScaleType::Pointer shiftScale = ShiftScaleType::New();
  shiftScale->SetInput(resampler->GetOutput());
  shiftScale->SetShift(interceptShift);
#endif

  ////////////////////////////////////////////////
  // 5) Write the new DICOM series

  // Make the output directory and generate the file names.
  itksys::SystemTools::MakeDirectory(argv[2]);

  // Generate the file names
  OutputNamesGeneratorType::Pointer outputNames = OutputNamesGeneratorType::New();
  std::string                       seriesFormat(argv[2]);
  seriesFormat = seriesFormat + "/" + "IM%d.dcm";
  outputNames->SetSeriesFormat(seriesFormat.c_str());
  outputNames->SetStartIndex(1);
  outputNames->SetEndIndex(outputSize[2]);

  SeriesWriterType::Pointer seriesWriter = SeriesWriterType::New();
#if ((ITK_VERSION_MAJOR == 4) && (ITK_VERSION_MINOR < 6))
  seriesWriter->SetInput(shiftScale->GetOutput());
#else
  seriesWriter->SetInput(resampler->GetOutput());
#endif
  seriesWriter->SetImageIO(gdcmIO);
  seriesWriter->SetFileNames(outputNames->GetFileNames());
  seriesWriter->SetMetaDataDictionaryArray(&outputArray);
  try
  {
    seriesWriter->Update();
  }
  catch (itk::ExceptionObject & excp)
  {
    std::cerr << "Exception thrown while writing the series " << std::endl;
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "The output series in directory " << argv[2] << " has " << outputSize[2] << " files with spacing "
            << outputSpacing << std::endl;
  return EXIT_SUCCESS;
}

void
CopyDictionary(itk::MetaDataDictionary & fromDict, itk::MetaDataDictionary & toDict)
{
  using DictionaryType = itk::MetaDataDictionary;

  DictionaryType::ConstIterator itr = fromDict.Begin();
  DictionaryType::ConstIterator end = fromDict.End();
  using MetaDataStringType = itk::MetaDataObject<std::string>;

  while (itr != end)
  {
    itk::MetaDataObjectBase::Pointer entry = itr->second;

    MetaDataStringType::Pointer entryvalue = dynamic_cast<MetaDataStringType *>(entry.GetPointer());
    if (entryvalue)
    {
      std::string tagkey = itr->first;
      std::string tagvalue = entryvalue->GetMetaDataObjectValue();
      itk::EncapsulateMetaData<std::string>(toDict, tagkey, tagvalue);
    }
    ++itr;
  }
}
