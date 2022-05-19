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
#include "itkPolyLineParametricPath.h"

int
main()
{
  using PathType = itk::PolyLineParametricPath<2>;

  PathType::Pointer path = PathType::New();
  path->Initialize();

  using ContinuousIndexType = PathType::ContinuousIndexType;

  // Create a line
  for (unsigned int i = 0; i < 20; ++i)
  {
    ContinuousIndexType cindex;
    cindex[0] = 0;
    cindex[1] = i;
    path->AddVertex(cindex);
  }

  const PathType::VertexListType * vertexList = path->GetVertexList();

  for (unsigned int i = 0; i < vertexList->Size(); ++i)
  {
    std::cout << vertexList->GetElement(i) << std::endl;
  }

  return EXIT_SUCCESS;
}
