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

#include "itkIndex.h"
#include "itkOffset.h"

#include <iostream>

int
main()
{
  constexpr unsigned int Dimension = 2;

  itk::Index<Dimension> index;
  index.Fill(5);

  itk::Offset<Dimension> offset;
  offset.Fill(1);

  std::cout << "index: " << index << std::endl;
  std::cout << "offset: " << offset << std::endl;
  std::cout << "index + offset: " << index + offset << std::endl;
  std::cout << std::endl;

  offset[0] = -1;

  std::cout << "index: " << index << std::endl;
  std::cout << "offset: " << offset << std::endl;
  std::cout << "index + offset: " << index + offset << std::endl;
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
