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
#include <itkDerivativeOperator.h>

int
main()
{
  using DerivativeOperatorType = itk::DerivativeOperator<float, 2>;
  DerivativeOperatorType derivativeOperator;
  derivativeOperator.SetDirection(0); // Create the operator for the X axis derivative
  itk::Size<2> radius;
  radius.Fill(1);
  derivativeOperator.CreateToRadius(radius);

  std::cout << "Size: " << derivativeOperator.GetSize() << std::endl;

  std::cout << derivativeOperator << std::endl;

  for (unsigned int i = 0; i < 9; ++i)
  {
    std::cout << derivativeOperator.GetOffset(i) << " " << derivativeOperator.GetElement(i) << std::endl;
  }
  return EXIT_SUCCESS;
}
