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

#include "itkVectorContainer.h"
#include "itkPoint.h"

int
main()
{
  constexpr unsigned int Dimension = 2;
  using CoordType = double;

  using PointType = itk::Point<CoordType, Dimension>;
  using VectorContainerType = itk::VectorContainer<int, PointType>;

  PointType p0;
  p0[0] = 1.0;
  p0[1] = 2.0;

  PointType p1;
  p1[0] = 2.0;
  p1[1] = 3.0;

  auto points = VectorContainerType::New();
  points->Reserve(2);

  VectorContainerType::Iterator point = points->Begin();
  point->Value() = p0;

  ++point;
  point->Value() = p1;

  point = points->Begin();
  while (point != points->End())
  {
    std::cout << point->Value() << std::endl;
    ++point;
  }

  return EXIT_SUCCESS;
}
