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

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkCastImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << "<InputFileName> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  const char * inputImage = argv[1];
  const char * outputImage = argv[2];

  using InputPixelType = float;
  using OutputPixelType = unsigned char;
  using InputImageType = itk::Image<InputPixelType, Dimension>;
  using OutputImageType = itk::Image<OutputPixelType, Dimension>;

  const auto input = itk::ReadImage<InputImageType>(inputImage);

  using RescaleType = itk::RescaleIntensityImageFilter<InputImageType, InputImageType>;
  auto rescale = RescaleType::New();
  rescale->SetInput(input);
  rescale->SetOutputMinimum(0);
  rescale->SetOutputMaximum(itk::NumericTraits<OutputPixelType>::max());

  using FilterType = itk::CastImageFilter<InputImageType, OutputImageType>;
  auto filter = FilterType::New();
  filter->SetInput(rescale->GetOutput());

  try
  {
    itk::WriteImage(filter->GetOutput(), outputImage);
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
