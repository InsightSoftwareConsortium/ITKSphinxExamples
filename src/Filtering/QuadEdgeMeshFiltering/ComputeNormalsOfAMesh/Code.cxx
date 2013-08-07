#include "itkVector.h"
#include "itkQuadEdgeMesh.h"
#include "itkMeshFileReader.h"
#include "itkQuadEdgeMeshExtendedTraits.h"
#include "itkNormalQuadEdgeMeshFilter.h"

int main( int argc, char* argv[] )
{
  if( argc < 2 )
    {
    std::cerr << "Usage:" <<std::endl;
    std::cerr << argv[0] << "<InputFileName> <WeightType>" << std::endl;
    std::cerr << "Weight type: " << std::endl;
    std::cerr << "  * 0:  GOURAUD" << std::endl;
    std::cerr << "  * 1:  THURMER" << std::endl;
    std::cerr << "  * 2:  AREA" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int    Dimension = 3;
  typedef double        CoordType;

  typedef itk::QuadEdgeMesh< CoordType, Dimension > InputMeshType;

  typedef itk::Vector< CoordType, Dimension > VectorType;

  typedef itk::QuadEdgeMeshExtendedTraits <
    VectorType,
    Dimension,
    2,
    CoordType,
    CoordType,
    VectorType,
    bool,
    bool > Traits;

  typedef itk::MeshFileReader< InputMeshType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New( );
  reader->SetFileName( argv[1] );
  reader->Update( );

  typedef itk::QuadEdgeMesh < VectorType, Dimension, Traits > OutputMeshType;

  typedef itk::NormalQuadEdgeMeshFilter< InputMeshType, OutputMeshType >
    NormalFilterType;
  NormalFilterType::WeightType weight_type;

  int param = atoi( argv[2] );

  if( ( param < 0 ) || ( param > 2 ) )
    {
    std::cerr <<"Weight type must be either: " <<std::endl;
    std::cerr <<"   * 0:  GOURAUD" <<std::endl;
    std::cerr <<"   * 1:  THURMER" <<std::endl;
    std::cerr <<"   * 2:  AREA" <<std::endl;
    return EXIT_FAILURE;
    }
  else
    {
    switch( param )
      {
      default:
      case 0:
        weight_type = NormalFilterType::GOURAUD;
        break;
      case 1:
        weight_type = NormalFilterType::THURMER;
        break;
      case 2:
        weight_type = NormalFilterType::AREA;
        break;
      }
    }

  NormalFilterType::Pointer normals = NormalFilterType::New( );
  normals->SetInput( reader->GetOutput() );
  normals->SetWeight( weight_type );
  normals->Update( );

  OutputMeshType::Pointer output = normals->GetOutput( );

  OutputMeshType::PointsContainerPointer    points = output->GetPoints();
  OutputMeshType::PointsContainerIterator   p_it = points->Begin();

  OutputMeshType::PointDataContainerPointer container = output->GetPointData();
  OutputMeshType::PointDataContainerIterator d_it = container->Begin();

  std::cout << "Index * Point * Normal" << std::endl;

  while( p_it != points->End() )
    {
    std::cout << p_it.Index() << " * ";
    std::cout << p_it.Value() << " * ";
    std::cout << d_it.Value() << std::endl;

    ++p_it;
    ++d_it;
    }

  return EXIT_SUCCESS;
}
