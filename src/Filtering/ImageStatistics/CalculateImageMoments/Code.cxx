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
#include "itkImageMomentsCalculator.h"

int
main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName>" << std::endl;
    std::cerr << "Prints image moments from unsigned short binary image.";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }
  const char * inputFileName = argv[1];

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned short;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(inputFileName);

  // clang-format off
  using FilterType = itk::ImageMomentsCalculator<ImageType>;
  // clang-format on
  auto filter = FilterType::New();
  filter->SetImage(input);
  filter->Compute();
  filter->Print(std::cout, 0);

  return EXIT_SUCCESS;
}
