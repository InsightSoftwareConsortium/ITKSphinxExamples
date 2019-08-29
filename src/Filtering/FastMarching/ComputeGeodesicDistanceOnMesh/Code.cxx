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

#include "itkFastMarchingQuadEdgeMeshFilterBase.h"
#include "itkQuadEdgeMeshExtendedTraits.h"
#include "itkRegularSphereMeshSource.h"
#include "itkFastMarchingThresholdStoppingCriterion.h"
#include "itkMeshFileReader.h"
#include "itkMeshFileWriter.h"

int
main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << std::endl;
    std::cerr << " <input filename> <output filename>" << std::endl;
    return EXIT_FAILURE;
  }
  using PixelType = float;
  using CoordType = double;

  constexpr unsigned int Dimension = 3;

  using Traits = itk::QuadEdgeMeshExtendedTraits<PixelType, // type of data for vertices
                                                 Dimension, // geometrical dimension of space
                                                 2,         // Mac topological dimension of a cell
                                                 CoordType, // type for point coordinate
                                                 CoordType, // type for interpolation weight
                                                 PixelType, // type of data for cell
                                                 bool,      // type of data for primal edges
                                                 bool       // type of data for dual edges
                                                 >;

  using MeshType = itk::QuadEdgeMesh<PixelType, Dimension, Traits>;

  using ReaderType = itk::MeshFileReader<MeshType>;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(argv[1]);

  using FastMarchingType = itk::FastMarchingQuadEdgeMeshFilterBase<MeshType, MeshType>;

  MeshType::Pointer mesh = reader->GetOutput();

  MeshType::PointsContainerConstPointer points = mesh->GetPoints();

  MeshType::PointsContainerConstIterator pIt = points->Begin();
  MeshType::PointsContainerConstIterator pEnd = points->End();

  while (pIt != pEnd)
  {
    mesh->SetPointData(pIt->Index(), 1.);
    ++pIt;
  }

  using NodePairType = FastMarchingType::NodePairType;
  using NodePairContainerType = FastMarchingType::NodePairContainerType;

  NodePairContainerType::Pointer trial = NodePairContainerType::New();

  NodePairType nodePair(0, 0.);
  trial->push_back(nodePair);

  using CriterionType = itk::FastMarchingThresholdStoppingCriterion<MeshType, MeshType>;
  CriterionType::Pointer criterion = CriterionType::New();
  criterion->SetThreshold(100.);

  FastMarchingType::Pointer fmmFilter = FastMarchingType::New();
  fmmFilter->SetInput(mesh);
  fmmFilter->SetTrialPoints(trial);
  fmmFilter->SetStoppingCriterion(criterion);

  using WriterType = itk::MeshFileWriter<MeshType>;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput(fmmFilter->GetOutput());
  writer->SetFileName(argv[2]);

  try
  {
    writer->Update();
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
