#include "itkMeshFileReader.h"
#include "itkQuadEdgeMesh.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <VertexId>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 3;

  typedef double                                    PixelType;
  typedef itk::QuadEdgeMesh< PixelType, Dimension > MeshType;

  typedef itk::MeshFileReader< MeshType >  ReaderType;
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

  MeshType::PointIdentifier id = atoi( argv[2] );

  MeshType::QEType* qe = mesh->FindEdge( id );

  MeshType::QEType* temp = qe;
  do
    {
    std::cout << temp->GetLeft() << std::endl;
    temp = temp->GetOnext();
    } while( qe != temp );

  return EXIT_SUCCESS;
}
