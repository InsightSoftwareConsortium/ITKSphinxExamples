/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
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
#include "itkLabelMapOverlayImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <LabelMap> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * labelFileName = argv[2];
  const char * outputFileName = argv[3];

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(inputFileName);
  const auto label = itk::ReadImage<ImageType>(labelFileName);

  using LabelType = PixelType;
  using LabelObjectType = itk::LabelObject<LabelType, Dimension>;
  using LabelMapType = itk::LabelMap<LabelObjectType>;

  using ConverterType = itk::LabelImageToLabelMapFilter<ImageType, LabelMapType>;
  auto converter = ConverterType::New();
  converter->SetInput(label);

  using FilterType = itk::LabelMapOverlayImageFilter<LabelMapType, ImageType>;
  auto filter = FilterType::New();
  filter->SetInput(converter->GetOutput());
  filter->SetFeatureImage(input);
  filter->SetOpacity(0.5);

  try
  {
    itk::WriteImage(filter->GetOutput(), outputFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
