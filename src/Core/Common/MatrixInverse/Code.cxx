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
#include <itkMatrix.h>

#include <iostream>

int
main()
{
  using MatrixType = itk::Matrix<double, 2, 2>;
  MatrixType M;
  M(0, 0) = 1.0;
  M(0, 1) = 2.0;
  M(1, 0) = 3.0;
  M(1, 1) = 5.0;

  std::cout << "M: " << M << std::endl;

  MatrixType Minv(M.GetInverse());

  std::cout << "Inverse: " << Minv << std::endl;

  return EXIT_SUCCESS;
}
