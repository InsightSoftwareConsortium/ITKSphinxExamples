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

#include "itkCovariantVector.h"

int main(int, char*[])
{
  typedef itk::CovariantVector<double, 3> VectorType;
  VectorType v;
  v[0] = 1.0;
  v[1] = 2.0;
  v[2] = 3.0;

  std::cout << "v: " << v << std::endl;

  // norm
  VectorType::RealValueType vnorm = v.GetNorm();
  std::cout << "vnorm: " << vnorm << std::endl;

  VectorType::RealValueType vnorm2 = v.GetSquaredNorm();
  std::cout << "vnorm2: " << vnorm2 << std::endl;

  VectorType u = v;

  // normalization
  v.Normalize();
  std::cout << "v: " << v << std::endl;

  // another way to normalize
  if( vnorm != 0. )
    {
    for( unsigned int i = 0; i < u.GetNumberOfComponents(); i++ )
      {
      u[i] /= vnorm;
      }
    }

  std::cout << "u: " << u << std::endl;

  if( ( u - v ).GetNorm() != 0. )
    {
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
