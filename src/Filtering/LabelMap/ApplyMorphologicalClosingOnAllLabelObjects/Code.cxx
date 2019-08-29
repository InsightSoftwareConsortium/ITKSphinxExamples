/*=========================================================================
 *
 *  Copyright Insight Software Consortium
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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkLabelImageToLabelMapFilter.h"
#include "itkLabelMapToLabelImageFilter.h"
#include "itkObjectByObjectLabelMapFilter.h"
#include "itkLabelUniqueLabelMapFilter.h"
#include "itkFlatStructuringElement.h"
#include "itkBinaryMorphologicalClosingImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> <radius>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char *       inputFileName = argv[1];
  const char *       outputFileName = argv[2];
  const unsigned int radiusValue = std::stoi(argv[3]);

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  using ReaderType = itk::ImageFileReader<ImageType>;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(inputFileName);

  using LabelObjectType = itk::LabelObject<PixelType, Dimension>;
  using LabelMapType = itk::LabelMap<LabelObjectType>;

  using LabelImageToLabelMapFilterType = itk::LabelImageToLabelMapFilter<ImageType, LabelMapType>;
  LabelImageToLabelMapFilterType::Pointer labelMapConverter = LabelImageToLabelMapFilterType::New();
  labelMapConverter->SetInput(reader->GetOutput());
  labelMapConverter->SetBackgroundValue(itk::NumericTraits<PixelType>::Zero);

  using StructuringElementType = itk::FlatStructuringElement<Dimension>;
  StructuringElementType::RadiusType radius;
  radius.Fill(radiusValue);

  StructuringElementType structuringElement = StructuringElementType::Ball(radius);

  using MorphologicalFilterType =
    itk::BinaryMorphologicalClosingImageFilter<ImageType, ImageType, StructuringElementType>;
  MorphologicalFilterType::Pointer closingFilter = MorphologicalFilterType::New();

  using ObjectByObjectLabelMapFilterType = itk::ObjectByObjectLabelMapFilter<LabelMapType>;
  ObjectByObjectLabelMapFilterType::Pointer objectByObjectLabelMapFilter = ObjectByObjectLabelMapFilterType::New();
  objectByObjectLabelMapFilter->SetInput(labelMapConverter->GetOutput());
  objectByObjectLabelMapFilter->SetBinaryInternalOutput(true);
  objectByObjectLabelMapFilter->SetFilter(closingFilter);

  using UniqueLabelMapFilterType = itk::LabelUniqueLabelMapFilter<LabelMapType>;
  UniqueLabelMapFilterType::Pointer unique = UniqueLabelMapFilterType::New();
  unique->SetInput(objectByObjectLabelMapFilter->GetOutput());

  using LabelMapToLabelImageFilterType = itk::LabelMapToLabelImageFilter<LabelMapType, ImageType>;
  LabelMapToLabelImageFilterType::Pointer labelImageConverter = LabelMapToLabelImageFilterType::New();
  labelImageConverter->SetInput(unique->GetOutput());

  using WriterType = itk::ImageFileWriter<ImageType>;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(outputFileName);
  writer->SetInput(labelImageConverter->GetOutput());
  try
  {
    writer->Update();
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
