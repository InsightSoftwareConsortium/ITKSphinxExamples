#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkAntiAliasBinaryImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc < 3 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " <inputImage> <outputImage>";
    std::cerr << " [maximumRMSError]";
    std::cerr << " [numberOfIterations]";
    std::cerr << " [numberOfLayers]" << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];
  double maximumRMSError = 0.001;
  if( argc > 3 )
    {
    maximumRMSError = atof( argv[3] );
    }
  int numberOfIterations = 50;
  if( argc > 4 )
    {
    numberOfIterations = atoi( argv[4] );
    }
  int numberOfLayers = 2;
  if( argc > 5 )
    {
    numberOfLayers = atoi( argv[5] );
    }

  const unsigned int Dimension = 2;

  typedef float      PixelType;

  typedef itk::Image< PixelType, Dimension >    ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  typedef itk::AntiAliasBinaryImageFilter< ImageType, ImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetMaximumRMSError( maximumRMSError );
  filter->SetNumberOfIterations( numberOfIterations );
  filter->SetNumberOfLayers( numberOfLayers );

  typedef itk::ImageFileWriter< ImageType > WriterType;
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
