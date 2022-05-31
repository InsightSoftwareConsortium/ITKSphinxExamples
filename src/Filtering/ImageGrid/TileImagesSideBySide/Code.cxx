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
#include "itkTileImageFilter.h"

int
main(int argc, char * argv[])
{
  // Verify arguments
  if (argc < 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "input1 input2 output" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse arguments
  std::string input1FileName = argv[1];
  std::string input2FileName = argv[2];
  std::string outputFileName = argv[3];

  // Output arguments
  std::cout << "input1FileName " << input1FileName << std::endl;
  std::cout << "input2FileName " << input2FileName << std::endl;
  ;
  std::cout << "outputFileName " << outputFileName << std::endl;
  ;

  using ImageType = itk::Image<unsigned char, 2>;

  // Read images
  const auto input1 = itk::ReadImage<ImageType>(input1FileName);
  const auto input2 = itk::ReadImage<ImageType>(input2FileName);

  // Tile the images side-by-side
  using TileFilterType = itk::TileImageFilter<ImageType, ImageType>;

  auto tileFilter = TileFilterType::New();

  itk::FixedArray<unsigned int, 2> layout;

  layout[0] = 2;
  layout[1] = 0;

  tileFilter->SetLayout(layout);

  tileFilter->SetInput(0, input1);
  tileFilter->SetInput(1, input2);

  // Set the value of output pixels which are created by mismatched size input images.
  // If the two images are the same height, this will not be used.
  unsigned char fillerValue = 128;
  tileFilter->SetDefaultPixelValue(fillerValue);
  tileFilter->Update();

  itk::WriteImage(tileFilter->GetOutput(), outputFileName);

  return EXIT_SUCCESS;
}
