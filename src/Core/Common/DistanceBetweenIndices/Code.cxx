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

#include "itkPoint.h"
#include "itkIndex.h"
#include "itkMath.h"

#include <iostream>

int
main()
{
  itk::Index<2> pixel1;
  pixel1.Fill(2);

  itk::Index<2> pixel2;
  pixel2.Fill(4);

  itk::Point<double, 2> p1;
  p1[0] = pixel1[0];
  p1[1] = pixel1[1];

  itk::Point<double, 2> p2;
  p2[0] = pixel2[0];
  p2[1] = pixel2[1];

  double distance = p2.EuclideanDistanceTo(p1);
  std::cout << "Distance: " << distance << std::endl;
}
