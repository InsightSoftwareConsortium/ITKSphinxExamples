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

#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryMorphologicalOpeningImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkSignedMaurerDistanceMapImageFilter.h"
#include "itkVotingBinaryIterativeHoleFillingImageFilter.h"
#include "itkWatershedImageFilter.h"

// Run with:
// ./SegmentWithWatershedAndDistanceMap <inputImageFile>
// <reversedInputImageFile> <distanceMapOutputImageFile>
// <watershedOutputFileName> <segmentationResultOutputImageFile>
// binarizingRadius majorityThreshold watershedThreshold watershedLevel
// cleaningStructuringElementRadius
// e.g.
// ./SegmentWithWatershedAndDistanceMap PlateauBorder.tif
// reversedInputImage.tif distanceMap.tif watershed.tif segmentationResult.tif
// 2 2 0.01 0.5 3
// (A rule of thumb is to set the threshold to be about 1 / 100 of the level.)

int
main(int argc, char * argv[])
{
  if (argc < 10)
  {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << argv[0] << " inputImageFile"
              << " reversedInputImageFile"
              << " distanceMapOutputImageFile"
              << " watershedOutputFileName"
              << " segmentationResultOutputImageFile"
              << " binarizingRadius"
              << " majorityThreshold"
              << " watershedThreshold"
              << " watershedLevel"
              << " cleaningStructuringElementRadius" << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 3;

  using UnsignedCharPixelType = unsigned char;
  using FloatPixelType = float;

  using InputImageType = itk::Image<UnsignedCharPixelType, Dimension>;
  using FloatImageType = itk::Image<FloatPixelType, Dimension>;
  using RGBPixelType = itk::RGBPixel<UnsignedCharPixelType>;
  using RGBImageType = itk::Image<RGBPixelType, Dimension>;
  using LabeledImageType = itk::Image<itk::IdentifierType, Dimension>;


  using FileReaderType = itk::ImageFileReader<InputImageType>;
  FileReaderType::Pointer reader = FileReaderType::New();
  reader->SetFileName(argv[1]);
  reader->Update();


  // Create bubble image: get a binarized version of the input image
  using VotingBinaryIterativeHoleFillingImageFilterType =
    itk::VotingBinaryIterativeHoleFillingImageFilter<InputImageType>;
  VotingBinaryIterativeHoleFillingImageFilterType::Pointer votingBinaryHoleFillingImageFilter =
    VotingBinaryIterativeHoleFillingImageFilterType::New();
  votingBinaryHoleFillingImageFilter->SetInput(reader->GetOutput());

  const unsigned int binarizingRadius = std::stoi(argv[6]);

  InputImageType::SizeType indexRadius;
  indexRadius.Fill(binarizingRadius);

  votingBinaryHoleFillingImageFilter->SetRadius(indexRadius);

  votingBinaryHoleFillingImageFilter->SetBackgroundValue(0);
  votingBinaryHoleFillingImageFilter->SetForegroundValue(255);

  const unsigned int majorityThreshold = std::stoi(argv[7]);
  votingBinaryHoleFillingImageFilter->SetMajorityThreshold(majorityThreshold);

  votingBinaryHoleFillingImageFilter->Update();

  using FileWriterType = itk::ImageFileWriter<InputImageType>;
  FileWriterType::Pointer reversedImageWriter = FileWriterType::New();
  reversedImageWriter->SetFileName(argv[2]);
  reversedImageWriter->SetInput(votingBinaryHoleFillingImageFilter->GetOutput());
  reversedImageWriter->Update();


  // Get the distance map of the input image
  using SignedMaurerDistanceMapImageFilterType =
    itk::SignedMaurerDistanceMapImageFilter<InputImageType, FloatImageType>;
  SignedMaurerDistanceMapImageFilterType::Pointer distanceMapImageFilter =
    SignedMaurerDistanceMapImageFilterType::New();
  distanceMapImageFilter->SetInput(votingBinaryHoleFillingImageFilter->GetOutput());

  distanceMapImageFilter->SetInsideIsPositive(false);
  distanceMapImageFilter->Update();


  using DistanceMapFileWriterType = itk::ImageFileWriter<FloatImageType>;
  DistanceMapFileWriterType::Pointer distanceMapWriter = DistanceMapFileWriterType::New();
  distanceMapWriter->SetFileName(argv[3]);
  distanceMapWriter->SetInput(distanceMapImageFilter->GetOutput());
  distanceMapWriter->Update();


  // Apply the watershed segmentation
  using WatershedFilterType = itk::WatershedImageFilter<FloatImageType>;
  WatershedFilterType::Pointer watershed = WatershedFilterType::New();

  const float watershedThreshold = std::stod(argv[8]);
  const float watershedLevel = std::stod(argv[9]);

  watershed->SetThreshold(watershedThreshold);
  watershed->SetLevel(watershedLevel);

  watershed->SetInput(distanceMapImageFilter->GetOutput());
  watershed->Update();


  using RGBFilterType = itk::ScalarToRGBColormapImageFilter<LabeledImageType, RGBImageType>;
  RGBFilterType::Pointer colormapImageFilter = RGBFilterType::New();
  colormapImageFilter->SetColormap(RGBFilterType::Jet);
  colormapImageFilter->SetInput(watershed->GetOutput());
  colormapImageFilter->Update();

  using WatershedFileWriterType = itk::ImageFileWriter<RGBImageType>;
  WatershedFileWriterType::Pointer watershedWriter = WatershedFileWriterType::New();
  watershedWriter->SetFileName(argv[4]);
  watershedWriter->SetInput(colormapImageFilter->GetOutput());
  watershedWriter->Update();


  // Clean the segmentation image: remove small objects by performing an
  // opening morphological operation
  using StructuringElementType =
    itk::BinaryBallStructuringElement<LabeledImageType::PixelType, LabeledImageType::ImageDimension>;
  StructuringElementType structuringElement;

  const unsigned int cleaningStructuringElementRadius = std::stoi(argv[10]);
  structuringElement.SetRadius(cleaningStructuringElementRadius);
  structuringElement.CreateStructuringElement();

  using BinaryMorphologicalOpeningImageFilterType =
    itk::BinaryMorphologicalOpeningImageFilter<LabeledImageType, LabeledImageType, StructuringElementType>;
  BinaryMorphologicalOpeningImageFilterType::Pointer openingFilter = BinaryMorphologicalOpeningImageFilterType::New();
  openingFilter->SetInput(watershed->GetOutput());
  openingFilter->SetKernel(structuringElement);
  openingFilter->Update();


  using SegmentationFileWriterType = itk::ImageFileWriter<RGBImageType>;
  SegmentationFileWriterType::Pointer segmentationWriter = SegmentationFileWriterType::New();
  segmentationWriter->SetFileName(argv[5]);
  segmentationWriter->SetInput(colormapImageFilter->GetOutput());
  segmentationWriter->Update();


  return EXIT_SUCCESS;
}
