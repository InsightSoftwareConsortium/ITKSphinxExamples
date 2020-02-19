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

#include "itkSize.h"

int
main(int, char *[])
{
  constexpr unsigned int Dimension = 2;
  itk::Size<Dimension>   size;

  // Method 1
  // set both components (size[0] and size[1]) to the same value
  // (in this case, 0).
  size.Fill(0);
  std::cout << size << std::endl;

  // Method 2
  // set each component separately.
  size[0] = 1;
  size[1] = 2;

  std::cout << size << std::endl;

  return EXIT_SUCCESS;
}
