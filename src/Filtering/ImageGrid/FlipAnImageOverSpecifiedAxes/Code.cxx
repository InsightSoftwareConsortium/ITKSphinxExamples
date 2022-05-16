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

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkFlipImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> <AxisToFlip>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(argv[1]);

  using FlipImageFilterType = itk::FlipImageFilter<ImageType>;

  FlipImageFilterType::Pointer flipFilter = FlipImageFilterType::New();
  flipFilter->SetInput(input);

  FlipImageFilterType::FlipAxesArrayType flipAxes;
  if (std::stoi(argv[3]) == 0)
  {
    flipAxes[0] = true;
    flipAxes[1] = false;
  }
  else
  {
    flipAxes[0] = false;
    flipAxes[1] = true;
  }

  flipFilter->SetFlipAxes(flipAxes);

  try
  {
    itk::WriteImage(flipFilter->GetOutput(), argv[2]);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
