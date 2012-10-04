#include "itkMeshFileReader.h"
#include "itkMeshFileWriter.h"
#include "itkQuadEdgeMesh.h"

#include "itkDelaunayConformingQuadEdgeMeshFilter.h"

int main( int argc, char* argv[] )
{
  // ** ERROR MESSAGE AND HELP ** //
  if( argc != 3 )
    {
    std::cerr << "Usage:" <<std::endl;
    std::cerr << argv[0] << " <InputFileName> <OutputFileName>" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int    Dimension = 3;
  typedef double        CoordType;

  typedef itk::QuadEdgeMesh< CoordType, 3 >                  MeshType;
  typedef itk::MeshFileReader< MeshType >                    ReaderType;
  typedef itk::MeshFileWriter< MeshType >                    WriterType;

  // ** READ THE FILE IN **
  ReaderType::Pointer reader = ReaderType::New( );
  reader->SetFileName( argv[1] );
  try
    {
    reader->Update( );
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << "Exception thrown while reading the input file " << std::endl;
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  MeshType::Pointer mesh = reader->GetOutput( );

  typedef itk::DelaunayConformingQuadEdgeMeshFilter< MeshType, MeshType >
  DelaunayConformFilterType;
  DelaunayConformFilterType::Pointer filter = DelaunayConformFilterType::New( );
  filter->SetInput( mesh );
  filter->Update( );

  // ** WRITE OUTPUT **
  WriterType::Pointer writer = WriterType::New( );
  writer->SetInput( filter->GetOutput( ) );
  writer->SetFileName( argv[2] );
  writer->Update( );

  std::cout << "Number of Edge flipped performed: "
            << filter->GetNumberOfEdgeFlips( ) <<std::endl;

  return EXIT_SUCCESS;
}