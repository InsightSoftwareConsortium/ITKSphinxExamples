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

#include "itkBresenhamLine.h"
#include "itkVector.h"
#include "itkOffset.h"
#include "itkPoint.h"

#include <iostream>

static void
Vector();
static void
Line();

int
main(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  Vector();
  Line();

  return EXIT_SUCCESS;
}

void
Vector()
{

  itk::BresenhamLine<2> line;

  itk::Vector<float, 2> v;
  v[0] = 1;
  v[1] = 1;
  std::vector<itk::Offset<2>> offsets = line.BuildLine(v, 4);

  for (auto offset : offsets)
  {
    std::cout << offset << std::endl;
  }
}

void
Line()
{

  itk::BresenhamLine<2> line;
  itk::Index<2>         pixel0;
  pixel0[0] = 0;
  pixel0[1] = 0;

  itk::Index<2> pixel1;
  pixel1[0] = 5;
  pixel1[1] = 5;

  std::vector<itk::Index<2>> pixels = line.BuildLine(pixel0, pixel1);

  for (auto pixel : pixels)
  {
    std::cout << pixel << std::endl;
  }
}
