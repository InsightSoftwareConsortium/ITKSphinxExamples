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

#include "itkQuadEdgeMesh.h"
#include "itkMeshFileWriter.h"

int
main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * outputFileName = argv[1];

  constexpr unsigned int Dimension = 3;

  using CoordType = double;
  using MeshType = itk::QuadEdgeMesh<CoordType, Dimension>;

  auto mesh = MeshType::New();

  using PointsContainer = MeshType::PointsContainer;
  using PointsContainerPointer = MeshType::PointsContainerPointer;

  PointsContainerPointer points = PointsContainer::New();
  points->Reserve(100);

  using PointType = MeshType::PointType;
  PointType p;
  p[2] = 0.;

  using PointIdentifier = MeshType::PointIdentifier;
  PointIdentifier k = 0;

  for (int i = 0; i < 10; ++i)
  {
    p[0] = static_cast<CoordType>(i);

    for (int j = 0; j < 10; ++j)
    {
      p[1] = static_cast<CoordType>(j);
      points->SetElement(k, p);
      k++;
    }
  }

  mesh->SetPoints(points);

  k = 0;

  for (int i = 0; i < 9; ++i)
  {
    for (int j = 0; j < 9; ++j)
    {
      mesh->AddFaceTriangle(k, k + 1, k + 11);
      mesh->AddFaceTriangle(k, k + 11, k + 10);
      k++;
    }
    k++;
  }

  using WriterType = itk::MeshFileWriter<MeshType>;
  auto writer = WriterType::New();
  writer->SetFileName(outputFileName);
  writer->SetInput(mesh);
  try
  {
    writer->Update();
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
