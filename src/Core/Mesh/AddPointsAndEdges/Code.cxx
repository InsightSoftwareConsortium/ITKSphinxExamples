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
#include "itkMesh.h"
#include "itkLineCell.h"

constexpr unsigned int Dimension = 3;
using MeshType = itk::Mesh<float, Dimension>;

MeshType::Pointer
CreatePointOnlyMesh();
void
CreateMeshWithEdges();

int
main()
{
  // CreatePointOnlyMesh();
  CreateMeshWithEdges();

  return 0;
}


MeshType::Pointer
CreatePointOnlyMesh()
{
  auto mesh = MeshType::New();

  // Create points
  MeshType::PointType p0, p1, p2, p3;

  p0[0] = -1.0;
  p0[1] = -1.0;
  p0[2] = 0.0; // first  point ( -1, -1, 0 )
  p1[0] = 1.0;
  p1[1] = -1.0;
  p1[2] = 0.0; // second point (  1, -1, 0 )
  p2[0] = 1.0;
  p2[1] = 1.0;
  p2[2] = 0.0; // third  point (  1,  1, 0 )
  p3[0] = 1.0;
  p3[1] = 1.0;
  p3[2] = 1.0; // third  point (  1,  1, 1 )

  mesh->SetPoint(0, p0);
  mesh->SetPoint(1, p1);
  mesh->SetPoint(2, p2);
  mesh->SetPoint(3, p3);

  std::cout << "Points = " << mesh->GetNumberOfPoints() << std::endl;

  // Access points
  using PointsIterator = MeshType::PointsContainer::Iterator;

  PointsIterator pointIterator = mesh->GetPoints()->Begin();

  PointsIterator end = mesh->GetPoints()->End();
  while (pointIterator != end)
  {
    MeshType::PointType p = pointIterator.Value(); // access the point
    std::cout << p << std::endl;                   // print the point
    ++pointIterator;                               // advance to next point
  }

  return mesh;
}

void
CreateMeshWithEdges()
{
  MeshType::Pointer mesh = CreatePointOnlyMesh();

  using CellAutoPointer = MeshType::CellType::CellAutoPointer;
  using LineType = itk::LineCell<MeshType::CellType>;

  // Create a link to the previous point in the column (below the current point)
  CellAutoPointer colline;
  colline.TakeOwnership(new LineType);

  // unsigned int pointId0 = 0;
  // unsigned int pointId1 = 1;

  unsigned int pointId0 = 2;
  unsigned int pointId1 = 3;

  colline->SetPointId(0, pointId0); // line between points 0 and 1
  colline->SetPointId(1, pointId1);
  // std::cout << "Linked point: " << MeshIndex << " and " << MeshIndex - 1 << std::endl;
  mesh->SetCell(0, colline);

  using CellIterator = MeshType::CellsContainer::Iterator;
  CellIterator cellIterator = mesh->GetCells()->Begin();
  CellIterator CellsEnd = mesh->GetCells()->End();

  while (cellIterator != CellsEnd)
  {
    MeshType::CellType * cellptr = cellIterator.Value();
    auto *               line = dynamic_cast<LineType *>(cellptr);

    itk::IdentifierType * linePoint0 = line->PointIdsBegin();
    // itk::IdentifierType* linePoint1 = line->PointIdsEnd();
    itk::IdentifierType * linePoint1 = linePoint0 + 1;
    std::cout << "line first point id: " << *linePoint0 << std::endl;
    std::cout << "line second point id: " << *linePoint1 << std::endl;

    ++cellIterator;
  }
}
