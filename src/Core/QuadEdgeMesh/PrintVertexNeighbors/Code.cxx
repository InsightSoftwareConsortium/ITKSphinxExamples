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

#include "itkMeshFileReader.h"
#include "itkQuadEdgeMesh.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << "<InputFileName> <VertexId>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  constexpr unsigned int Dimension = 3;
  using CoordinateType = double;
  using MeshType = itk::QuadEdgeMesh< CoordinateType, Dimension >;
  using ReaderType = itk::MeshFileReader< MeshType >;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  try
    {
    reader->Update();
    }
  catch( itk::ExceptionObject& e )
    {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
    }

  MeshType::Pointer mesh = reader->GetOutput();

  auto id = static_cast< MeshType::PointIdentifier >( atoi( argv[2] ) );

  MeshType::QEType* qe = mesh->FindEdge( id );
  if( qe == nullptr )
    {
    std::cerr << "Error: either this vertex does not exist, either this vertex is not connected." << std::endl;
    return EXIT_FAILURE;
    }

  MeshType::QEType* qe2 = qe;

  do
    {
    std::cout << qe->GetDestination() << std::endl;
    qe = qe->GetOnext();
    } while( qe2 != qe );

  return EXIT_SUCCESS;
}
