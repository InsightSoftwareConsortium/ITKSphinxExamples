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

  typedef double                                  CoordinateType;
  typedef itk::Mesh< CoordinateType, Dimension >  MeshType;

  typedef itk::MeshFileReader< MeshType >  ReaderType;
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
