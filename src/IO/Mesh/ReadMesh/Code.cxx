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

#include "itkMesh.h"
#include "itkMeshFileReader.h"
#include "itkMeshFileWriter.h"

int main( int argc, char* argv[] )
{
  if( ( argc != 2 ) && ( argc != 4 ) )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <id 1 (optional)> <id 2 (optional)>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 3;

  using CoordinateType = double;
  using MeshType = itk::Mesh< CoordinateType, Dimension >;

  using ReaderType = itk::MeshFileReader< MeshType >;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  MeshType::Pointer mesh = reader->GetOutput();

  if( argc == 4 )
    {
    MeshType::PointIdentifier id1 = atoi( argv[2] );
    MeshType::PointIdentifier id2 = atoi( argv[3] );

    MeshType::PointType p = mesh->GetPoint( id1 );
    MeshType::PointType q = mesh->GetPoint( id2 );

    std::cout << p.EuclideanDistanceTo( q ) << std::endl;
    }

  return EXIT_SUCCESS;
}
