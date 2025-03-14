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
#include <itkGaussianOperator.h>

int
main()
{
  using GaussianOperatorType = itk::GaussianOperator<float, 2>;
  GaussianOperatorType gaussianOperator;
  gaussianOperator.SetDirection(0); // Create the operator for the X axis derivative
  auto radius = itk::Size<2>::Filled(1);
  gaussianOperator.CreateToRadius(radius);

  std::cout << "Size: " << gaussianOperator.GetSize() << std::endl;

  std::cout << gaussianOperator << std::endl;

  for (unsigned int i = 0; i < 9; ++i)
  {
    std::cout << gaussianOperator.GetOffset(i) << " " << gaussianOperator.GetElement(i) << std::endl;
  }
  return EXIT_SUCCESS;
}
