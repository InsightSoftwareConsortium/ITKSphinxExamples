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

#include <itkBackwardDifferenceOperator.h>

int
main(int, char *[])
{
  using PixelType = float;
  constexpr unsigned int Dimension = 2;

  using BackwardDifferenceOperatorType = itk::BackwardDifferenceOperator<PixelType, Dimension>;
  BackwardDifferenceOperatorType backwardDifferenceOperator;

  // Create the operator for the X axis derivative
  backwardDifferenceOperator.SetDirection(0);

  itk::Size<Dimension> radius;
  radius.Fill(1);

  backwardDifferenceOperator.CreateToRadius(radius);

  std::cout << "Size: " << backwardDifferenceOperator.GetSize() << std::endl;

  std::cout << backwardDifferenceOperator << std::endl;

  for (unsigned int i = 0; i < 9; i++)
  {
    std::cout << backwardDifferenceOperator.GetOffset(i) << " " << backwardDifferenceOperator.GetElement(i)
              << std::endl;
  }
  return EXIT_SUCCESS;
}
