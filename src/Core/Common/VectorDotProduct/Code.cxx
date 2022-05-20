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

#include "itkVector.h"

int
main()
{
  constexpr unsigned int Dimension = 3;
  using CoordType = double;

  using VectorType = itk::Vector<CoordType, Dimension>;

  VectorType u;
  u[0] = -1.;
  u[1] = 1.;
  u[2] = -1.;

  VectorType v;
  v[0] = 1.;
  v[1] = 2.;
  v[2] = 3.;

  std::cout << "u :" << u << std::endl;
  std::cout << "v :" << v << std::endl;
  std::cout << "DotProduct( u, v ) = " << u * v << std::endl;
  std::cout << "u - ( u * v ) * v = " << u - (u * v) * v << std::endl;

  return EXIT_SUCCESS;
}
