#include "itkMesh.h"
#include "itkMeshFileReader.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkCastImageFilter.h"
#include "itkTriangleMeshToBinaryImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 4 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputImageName> <InputMeshName> <OutputImageName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputImageName   = argv[1];
  const char * inputMeshName    = argv[2];
  const char * outputImageName  = argv[3];

  const unsigned int Dimension = 3;
  typedef double MeshPixelType;

  typedef itk::Mesh< MeshPixelType, Dimension > MeshType;

  typedef itk::MeshFileReader< MeshType >  MeshReaderType;
  MeshReaderType::Pointer meshReader = MeshReaderType::New();
  meshReader->SetFileName( inputMeshName );

  typedef unsigned char                           InputPixelType;
  typedef itk::Image< InputPixelType, Dimension > InputImageType;
  typedef itk::ImageFileReader< InputImageType >  ImageReaderType;

  ImageReaderType::Pointer imageReader = ImageReaderType::New();
  imageReader->SetFileName( inputImageName );

  typedef unsigned char                             OutputPixelType;
  typedef itk::Image< OutputPixelType, Dimension >  OutputImageType;

  typedef itk::CastImageFilter< InputImageType, OutputImageType > CastFilterType;
  CastFilterType::Pointer cast = CastFilterType::New();
  cast->SetInput( imageReader->GetOutput() );

  typedef itk::TriangleMeshToBinaryImageFilter< MeshType, OutputImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( meshReader->GetOutput() );
  filter->SetInfoImage( cast->GetOutput() );
  filter->SetInsideValue( itk::NumericTraits< OutputPixelType >::max() );
  try
    {
    filter->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  typedef itk::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputImageName );
  writer->SetInput( filter->GetOutput() );
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
