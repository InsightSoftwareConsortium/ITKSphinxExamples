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

int
main(int argc, char * argv[])
{
  // Verify command line arguments
  if (argc < 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " inputImageFile" << std::endl;
    return EXIT_FAILURE;
  }

  using PixelType = unsigned char;

  using ImageType = itk::Image<PixelType, 2>;

  ImageType::Pointer image = itk::ReadImage<ImageType>(argv[1]);

  ImageType::RegionType region = image->GetLargestPossibleRegion();

  ImageType::SizeType size = region.GetSize();

  std::cout << size << std::endl;

  // An example image had w = 200 and h = 100
  // (it is wider than it is tall). The above output
  // 200 x 100
  // so w = GetSize()[0]
  // and h = GetSize()[1]

  // A pixel inside the region
  ImageType::IndexType indexInside;
  indexInside[0] = 150;
  indexInside[1] = 50;
  std::cout << region.IsInside(indexInside) << std::endl;

  // A pixel outside the region
  ImageType::IndexType indexOutside;
  indexOutside[0] = 50;
  indexOutside[1] = 150;
  std::cout << region.IsInside(indexOutside) << std::endl;

  // This means that the [0] component of the index is referencing the
  // left to right (x) value and the [1] component of Index is referencing
  // the top to bottom (y) value

  return EXIT_SUCCESS;
}
