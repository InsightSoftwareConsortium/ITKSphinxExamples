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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkLabelImageToLabelMapFilter.h"
#include "itkLabelMapToLabelImageFilter.h"
#include "itkLabelSelectionLabelMapFilter.h"
#include "itkMergeLabelMapFilter.h"
#include "itkObjectByObjectLabelMapFilter.h"
#include "itkLabelUniqueLabelMapFilter.h"
#include "itkFlatStructuringElement.h"
#include "itkBinaryMorphologicalClosingImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 5)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> <label> <radius>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const char *       inputFileName = argv[1];
  const char *       outputFileName = argv[2];
  const auto         label = static_cast<PixelType>(std::stoi(argv[3]));
  const unsigned int radiusValue = std::stoi(argv[4]);

  const auto input = itk::ReadImage<ImageType>(inputFileName);

  using LabelObjectType = itk::LabelObject<PixelType, Dimension>;
  using LabelMapType = itk::LabelMap<LabelObjectType>;

  using LabelImageToLabelMapFilterType = itk::LabelImageToLabelMapFilter<ImageType, LabelMapType>;
  LabelImageToLabelMapFilterType::Pointer labelMapConverter = LabelImageToLabelMapFilterType::New();
  labelMapConverter->SetInput(input);
  labelMapConverter->SetBackgroundValue(itk::NumericTraits<PixelType>::Zero);

  using SelectorType = itk::LabelSelectionLabelMapFilter<LabelMapType>;
  SelectorType::Pointer selector = SelectorType::New();
  selector->SetInput(labelMapConverter->GetOutput());
  selector->SetLabel(label);

  using StructuringElementType = itk::FlatStructuringElement<Dimension>;
  StructuringElementType::RadiusType radius;
  radius.Fill(radiusValue);

  StructuringElementType structuringElement = StructuringElementType::Ball(radius);

  using MorphologicalFilterType =
    itk::BinaryMorphologicalClosingImageFilter<ImageType, ImageType, StructuringElementType>;
  MorphologicalFilterType::Pointer closingFilter = MorphologicalFilterType::New();

  using ObjectByObjectLabelMapFilterType = itk::ObjectByObjectLabelMapFilter<LabelMapType>;
  ObjectByObjectLabelMapFilterType::Pointer objectByObjectLabelMapFilter = ObjectByObjectLabelMapFilterType::New();
  objectByObjectLabelMapFilter->SetInput(selector->GetOutput(0));
  objectByObjectLabelMapFilter->SetBinaryInternalOutput(true);
  objectByObjectLabelMapFilter->SetFilter(closingFilter);

  using MergeLabelFilterType = itk::MergeLabelMapFilter<LabelMapType>;
  MergeLabelFilterType::Pointer merger = MergeLabelFilterType::New();
  merger->SetInput(0, objectByObjectLabelMapFilter->GetOutput(0));
  merger->SetInput(1, selector->GetOutput(1));
  merger->SetMethod(itk::MergeLabelMapFilterEnums::ChoiceMethod::KEEP);

  using UniqueLabelMapFilterType = itk::LabelUniqueLabelMapFilter<LabelMapType>;
  UniqueLabelMapFilterType::Pointer unique = UniqueLabelMapFilterType::New();
  unique->SetInput(merger->GetOutput());

  using LabelMapToLabelImageFilterType = itk::LabelMapToLabelImageFilter<LabelMapType, ImageType>;
  LabelMapToLabelImageFilterType::Pointer labelImageConverter = LabelMapToLabelImageFilterType::New();
  labelImageConverter->SetInput(unique->GetOutput());

  try
  {
    itk::WriteImage(labelImageConverter->GetOutput(), outputFileName);
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
