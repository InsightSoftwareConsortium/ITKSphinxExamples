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
#include "itkRandomImageSource.h"
#include "itkImageFileWriter.h"
#include "itkAtanImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;
  using InputPixelType = unsigned char;

  using InputImageType = itk::Image<InputPixelType, Dimension>;

  auto size = InputImageType::SizeType::Filled(100);

  using RandomImageSourceType = itk::RandomImageSource<InputImageType>;

  auto randomImageSource = RandomImageSourceType::New();
  randomImageSource->SetNumberOfWorkUnits(1); // to produce non-random results
  randomImageSource->SetSize(size);

  using OutputPixelType = float;
  using OutputImageType = itk::Image<OutputPixelType, Dimension>;

  using FilterType = itk::AtanImageFilter<InputImageType, OutputImageType>;
  auto filter = FilterType::New();
  filter->SetInput(randomImageSource->GetOutput());

  try
  {
    itk::WriteImage(filter->GetOutput(), argv[1]);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
