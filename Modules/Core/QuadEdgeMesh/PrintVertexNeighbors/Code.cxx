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

  const unsigned int Dimension = 3;
  typedef double  CoordinateType;
  typedef itk::QuadEdgeMesh< CoordinateType, Dimension >  MeshType;
  typedef itk::MeshFileReader< MeshType >                 ReaderType;

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

  MeshType::PointIdentifier id = static_cast< MeshType::PointIdentifier >( atoi( argv[2] ) );

  MeshType::QEType* qe = mesh->FindEdge( id );
  if( qe == NULL )
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
