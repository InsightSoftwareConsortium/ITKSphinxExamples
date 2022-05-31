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
#include "itkQuadEdgeMeshPolygonCell.h"

#include "itkMeshFileReader.h"
#include "itkMeshFileWriter.h"

int
main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  constexpr unsigned int Dimension = 3;
  using CoordType = double;
  using MeshType = itk::QuadEdgeMesh<CoordType, Dimension>;
  using MeshPointer = MeshType::Pointer;
  using MeshPointsContainerPointer = MeshType::PointsContainerPointer;
  using MeshPointsContainerIterator = MeshType::PointsContainerIterator;
  using MeshPointType = MeshType::PointType;
  using MeshPointIdentifier = MeshType::PointIdentifier;
  using MeshCellIdentifier = MeshType::CellIdentifier;

  using ReaderType = itk::MeshFileReader<MeshType>;
  auto reader = ReaderType::New();
  reader->SetFileName(inputFileName);

  MeshPointer mesh = reader->GetOutput();

  MeshPointer output = MeshType::New();

  std::map<MeshPointIdentifier, MeshPointIdentifier> verticesMap;
  std::set<MeshCellIdentifier>                       facesSet;

  MeshPointsContainerPointer points = mesh->GetPoints();

  MeshPointsContainerIterator pIt = points->Begin();
  MeshPointsContainerIterator pEnd = points->End();

  while (pIt != pEnd)
  {
    MeshPointType p = pIt->Value();

    if ((p[2] < 0.))
    {
      // here you do not want to use operator = to copy the coordinates from the
      // input mesh to the output one. Indeed the operator = does not only copy
      // the coordinates, but also the pointer to first QuadEdge of the 0-ring,
      // and it would be wrong.
      MeshPointType q;
      q.CastFrom(p);

      verticesMap[pIt->Index()] = output->AddPoint(q);

      // iterate on the 0-ring (vertex neighbors)
      MeshType::QEType * qe = p.GetEdge();
      MeshType::QEType * temp = qe;
      do
      {
        // insert the corresponding faces into std::set
        facesSet.insert(temp->GetLeft());

        temp = temp->GetOnext();
      } while (qe != temp);
    }
    ++pIt;
  }

  MeshType::CellsContainerPointer cells = mesh->GetCells();

  using PolygonType = itk::QuadEdgeMeshPolygonCell<MeshType::CellType>;

  // iterate on the faces to be added into resulting mesh
  for (auto fIt : facesSet)
  {
    auto *                    face = dynamic_cast<PolygonType *>(cells->ElementAt(fIt));
    MeshType::PointIdentifier id[3];

    if (face)
    {
      MeshType::QEType * qe = face->GetEdgeRingEntry();
      MeshType::QEType * temp = qe;

      unsigned int k = 0;

      // iterate on the vertices of a given face
      do
      {
        // add the corresponding vertex into the output mesh if it has not been added yet
        if (verticesMap.find(temp->GetOrigin()) == verticesMap.end())
        {
          MeshType::PointType p = mesh->GetPoint(temp->GetOrigin());

          MeshType::PointType q;
          q.CastFrom(p);

          verticesMap[temp->GetOrigin()] = output->AddPoint(q);
        }
        id[k++] = verticesMap[temp->GetOrigin()];

        temp = temp->GetLnext();
      } while (qe != temp);

      // add the corresponding face into the output mesh
      output->AddFaceTriangle(id[0], id[1], id[2]);
    }
  }

  // save the corresponding mesh
  using MeshWriterType = itk::MeshFileWriter<MeshType>;
  auto writer = MeshWriterType::New();
  writer->SetInput(output);
  writer->SetFileName(outputFileName);

  try
  {
    writer->Update();
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
