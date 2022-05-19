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

#include "itkMeshFileReader.h"
#include "itkQuadEdgeMesh.h"

int
main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <VertexId>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 3;

  using PixelType = double;
  using MeshType = itk::QuadEdgeMesh<PixelType, Dimension>;

  using ReaderType = itk::MeshFileReader<MeshType>;
  auto reader = ReaderType::New();
  reader->SetFileName(argv[1]);
  try
  {
    reader->Update();
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  MeshType::Pointer mesh = reader->GetOutput();

  MeshType::PointIdentifier id = std::stoi(argv[2]);

  MeshType::QEType * qe = mesh->FindEdge(id);

  MeshType::QEType * temp = qe;
  do
  {
    std::cout << temp->GetLeft() << std::endl;
    temp = temp->GetOnext();
  } while (qe != temp);

  return EXIT_SUCCESS;
}
