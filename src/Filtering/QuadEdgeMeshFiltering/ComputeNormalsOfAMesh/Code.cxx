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

#include "itkVector.h"
#include "itkQuadEdgeMesh.h"
#include "itkMeshFileReader.h"
#include "itkQuadEdgeMeshExtendedTraits.h"
#include "itkNormalQuadEdgeMeshFilter.h"

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage:" << std::endl;
    std::cerr << argv[0] << "<InputFileName> <WeightType>" << std::endl;
    std::cerr << "Weight type: " << std::endl;
    std::cerr << "  * 0:  GOURAUD" << std::endl;
    std::cerr << "  * 1:  THURMER" << std::endl;
    std::cerr << "  * 2:  AREA" << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 3;
  using CoordType = double;

  using InputMeshType = itk::QuadEdgeMesh<CoordType, Dimension>;

  using VectorType = itk::Vector<CoordType, Dimension>;

  using Traits =
    itk::QuadEdgeMeshExtendedTraits<VectorType, Dimension, 2, CoordType, CoordType, VectorType, bool, bool>;

  using ReaderType = itk::MeshFileReader<InputMeshType>;
  auto reader = ReaderType::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  using OutputMeshType = itk::QuadEdgeMesh<VectorType, Dimension, Traits>;

  using NormalFilterType = itk::NormalQuadEdgeMeshFilter<InputMeshType, OutputMeshType>;
  NormalFilterType::WeightEnum weight_type;

  int param = std::stoi(argv[2]);

  if ((param < 0) || (param > 2))
  {
    std::cerr << "Weight type must be either: " << std::endl;
    std::cerr << "   * 0:  GOURAUD" << std::endl;
    std::cerr << "   * 1:  THURMER" << std::endl;
    std::cerr << "   * 2:  AREA" << std::endl;
    return EXIT_FAILURE;
  }
  else
  {
    switch (param)
    {
      default:
      case 0:
        weight_type = itk::NormalQuadEdgeMeshFilterEnums::Weight::GOURAUD;
        break;
      case 1:
        weight_type = itk::NormalQuadEdgeMeshFilterEnums::Weight::THURMER;
        break;
      case 2:
        weight_type = itk::NormalQuadEdgeMeshFilterEnums::Weight::AREA;
        break;
    }
  }

  auto normals = NormalFilterType::New();
  normals->SetInput(reader->GetOutput());
  normals->SetWeight(weight_type);
  normals->Update();

  OutputMeshType::Pointer output = normals->GetOutput();

  OutputMeshType::PointsContainerPointer  points = output->GetPoints();
  OutputMeshType::PointsContainerIterator p_it = points->Begin();

  OutputMeshType::PointDataContainerPointer  container = output->GetPointData();
  OutputMeshType::PointDataContainerIterator d_it = container->Begin();

  std::cout << "Index * Point * Normal" << std::endl;

  while (p_it != points->End())
  {
    std::cout << p_it.Index() << " * ";
    std::cout << p_it.Value() << " * ";
    std::cout << d_it.Value() << std::endl;

    ++p_it;
    ++d_it;
  }

  return EXIT_SUCCESS;
}
