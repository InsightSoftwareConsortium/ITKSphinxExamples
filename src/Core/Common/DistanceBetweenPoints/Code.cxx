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

#include "itkPoint.h"
#include "vnl/vnl_math.h"

#include <iostream>

int main(int, char *[])
{
  const unsigned int Dimension = 3;
  using CoordType = double;

  using PointType = itk::Point< CoordType, Dimension >;

  PointType p0;
  p0[0] = 0.0;
  p0[1] = 0.0;
  p0[2] = 0.0;

  PointType p1;
  p1[0] = 1.0;
  p1[1] = 1.0;
  p1[2] = 1.0;

  PointType::RealType dist = p0.EuclideanDistanceTo(p1);
  std::cout << "Dist: " << dist << std::endl;

  if( dist != p1.EuclideanDistanceTo(p0) )
    {
    std::cerr << "p0.EuclideanDistanceTo(p1) != p1.EuclideanDistanceTo(p0)"
              << std::endl;
    return EXIT_FAILURE;
    }

  if( p1.EuclideanDistanceTo( p1 ) != 0. )
    {
    std::cerr << "p1.EuclideanDistanceTo(p1) != 0."
              << std::endl;
    return EXIT_FAILURE;
    }

  PointType::RealType dist2 = p0.SquaredEuclideanDistanceTo(p1);
  std::cout << "Dist2: " << dist2 << std::endl;

  if( vnl_math_abs( dist2 - dist * dist ) < vnl_math::eps )
    {
    std::cerr << "dist2 != dist * dist" << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
