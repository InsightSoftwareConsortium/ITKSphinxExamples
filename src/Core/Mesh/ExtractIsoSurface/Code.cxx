#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkMesh.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkBinaryMask3DMeshSource.h"
#include "itkMeshFileWriter.h"

int main( int argc, char* argv[] )
{
  if( argc != 5 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> <Lower Threshold> <Upper Threshold>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  const unsigned int Dimension = 3;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  PixelType lowerThreshold = static_cast< PixelType >( atoi( argv[3] ) );
  PixelType upperThreshold = static_cast< PixelType >( atoi( argv[4] ) );

  typedef itk::BinaryThresholdImageFilter< ImageType, ImageType > BinaryThresholdFilterType;
  BinaryThresholdFilterType::Pointer threshold = BinaryThresholdFilterType::New();
  threshold->SetInput( reader->GetOutput() );
  threshold->SetLowerThreshold( lowerThreshold );
  threshold->SetUpperThreshold( upperThreshold );
  threshold->SetOutsideValue( 0 );

  typedef itk::Mesh< double, Dimension > MeshType;

  typedef itk::BinaryMask3DMeshSource< ImageType, MeshType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( threshold->GetOutput() );
  filter->SetObjectValue( 255 );

  typedef itk::MeshFileWriter< MeshType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
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
