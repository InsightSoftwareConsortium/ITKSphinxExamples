#include "itkQuadEdgeMesh.h"
#include "itkMeshFileReader.h"
#include "itkMeshFileWriter.h"
#include "VNLIterativeSparseSolverTraits.h"
#include "itkParameterizationQuadEdgeMeshFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 5 )
    {
    std::cout <<"Requires 4 arguments: " << std::endl;
    std::cout <<"1-Input file name " << std::endl;
    std::cout <<"2-Border Type" << std::endl;
    std::cout <<"   * 0: SQUARE" << std::endl;
    std::cout <<"   * 1: DISK" << std::endl;
    std::cout <<"3-CoefficientType Type" << std::endl;
    std::cout <<"   * 0: OnesMatrixCoefficients" << std::endl;
    std::cout <<"   * 1: InverseEuclideanDistanceMatrixCoefficients" << std::endl;
    std::cout <<"   * 2: ConformalMatrixCoefficients" << std::endl;
    std::cout <<"   * 3: AuthalicMatrixCoefficients" << std::endl;
    std::cout <<"   * 4: HarmonicMatrixCoefficients" << std::endl;
    std::cout <<"4-Output file name " << std::endl;

    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[4];

  typedef double                                                  CoordType;
  const unsigned int Dimension = 3;

  typedef itk::QuadEdgeMesh< CoordType, Dimension >               MeshType;
  typedef itk::MeshFileReader< MeshType >                         ReaderType;
  typedef itk::MeshFileWriter< MeshType >                         WriterType;
  typedef itk::BorderQuadEdgeMeshFilter< MeshType, MeshType >     BorderTransformType;
  typedef VNLIterativeSparseSolverTraits< CoordType >             SolverTraits;

  typedef itk::ParameterizationQuadEdgeMeshFilter< MeshType, MeshType, SolverTraits >   ParametrizationType;

  ReaderType::Pointer reader = ReaderType::New( );
  reader->SetFileName( inputFileName );

  MeshType::Pointer mesh = reader->GetOutput( );

  BorderTransformType::Pointer border_transform = BorderTransformType::New( );
  border_transform->SetInput( reader->GetOutput() );

  int border;
  std::stringstream ssout( argv[2] );
  ssout >> border;
  switch( border )  // choose border type
    {
    case 0: // square shaped domain
      border_transform->SetTransformType( BorderTransformType::SQUARE_BORDER_TRANSFORM );
      break;
    case 1: // disk shaped domain
      border_transform->SetTransformType( BorderTransformType::DISK_BORDER_TRANSFORM );
      break;
    default: // handle .... user ....
      std::cerr << "2nd argument must be " << std::endl;
      std::cerr << "0 for SQUARE BORDER TRANSFORM or "
                << "1 for DISK BORDER TRANSFORM" << std::endl;
      return EXIT_FAILURE;
    }

  std::cout << "Transform type is: " << border_transform->GetTransformType( ) << std::endl;

  // ** CHOOSE AND SET BARYCENTRIC WEIGHTS **
  itk::OnesMatrixCoefficients< MeshType >                     coeff0;
  itk::InverseEuclideanDistanceMatrixCoefficients< MeshType > coeff1;
  itk::ConformalMatrixCoefficients< MeshType >                coeff2;
  itk::AuthalicMatrixCoefficients< MeshType >                 coeff3;
  itk::HarmonicMatrixCoefficients< MeshType >                 coeff4;

  ParametrizationType::Pointer param = ParametrizationType::New( );
  param->SetInput( mesh );
  param->SetBorderTransform( border_transform );

  int param_type;
  std::stringstream ssout3( argv[3] );
  ssout3 >> param_type;

  switch( param_type )
    {
    case 0:
      param->SetCoefficientsMethod( &coeff0 );
      break;
    case 1:
      param->SetCoefficientsMethod( &coeff1 );
      break;
    case 2:
      param->SetCoefficientsMethod( &coeff2 );
      break;
    case 3:
      param->SetCoefficientsMethod( &coeff3 );
      break;
    case 4:
      param->SetCoefficientsMethod( &coeff4 );
      break;
    default:
      std::cerr << "3rd argument must be " << std::endl;
      std::cerr << "0, 1, 2, 3 or 4" << std::endl;
      std::cerr << "Here it is: " << param_type << std::endl;
      return EXIT_FAILURE;
    }

  WriterType::Pointer writer = WriterType::New( );
  writer->SetInput( param->GetOutput( ) );
  writer->SetFileName( outputFileName );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
