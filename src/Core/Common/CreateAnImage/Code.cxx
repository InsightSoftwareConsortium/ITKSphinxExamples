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

#include "itkImage.h"

int
main(int, char *[])
{
  using ImageType = itk::Image<unsigned char, 3>;
  ImageType::Pointer image = ImageType::New();

  ImageType::IndexType start;
  start[0] = 0; // first index on X
  start[1] = 0; // first index on Y
  start[2] = 0; // first index on Z

  ImageType::SizeType size;
  size[0] = 200; // size along X
  size[1] = 200; // size along Y
  size[2] = 200; // size along Z

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  std::cout << image << std::endl;

  return EXIT_SUCCESS;
}
