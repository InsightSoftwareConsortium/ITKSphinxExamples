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
#include "itkLabelObject.h"
#include "itkLabelMap.h"
#include "itkLabelImageToLabelMapFilter.h"
#include "itkLabelMapToLabelImageFilter.h"
#include "itkLabelSelectionLabelMapFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 5)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName1> <OutputFileName2> <Label>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const char * inputFileName = argv[1];
  const char * outputFileName[2];
  outputFileName[0] = argv[2];
  outputFileName[1] = argv[3];
  const auto label = static_cast<PixelType>(std::stoi(argv[4]));

  const auto input = itk::ReadImage<ImageType>(inputFileName);

  using LabelObjectType = itk::LabelObject<PixelType, Dimension>;
  using LabelMapType = itk::LabelMap<LabelObjectType>;

  using LabelImageToLabelMapFilterType = itk::LabelImageToLabelMapFilter<ImageType, LabelMapType>;
  auto labelMapConverter = LabelImageToLabelMapFilterType::New();
  labelMapConverter->SetInput(input);
  labelMapConverter->SetBackgroundValue(itk::NumericTraits<PixelType>::Zero);

  using SelectorType = itk::LabelSelectionLabelMapFilter<LabelMapType>;
  auto selector = SelectorType::New();
  selector->SetInput(labelMapConverter->GetOutput());
  selector->SetLabel(label);

  for (int i = 0; i < 2; ++i)
  {
    using LabelMapToLabelImageFilterType = itk::LabelMapToLabelImageFilter<LabelMapType, ImageType>;
    auto labelImageConverter = LabelMapToLabelImageFilterType::New();
    labelImageConverter->SetInput(selector->GetOutput(i));

    try
    {
      itk::WriteImage(labelImageConverter->GetOutput(), outputFileName[i]);
    }
    catch (const itk::ExceptionObject & error)
    {
      std::cerr << "Error: " << error << std::endl;
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
