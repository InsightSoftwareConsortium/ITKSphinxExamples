#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkSigmoidImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 7 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << " <OutputMin> <OutputMax> <Alpha> <Beta>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  const unsigned int Dimension = 2;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;
  typedef float                              ScalarType;

  const PixelType outputMinimum = static_cast<PixelType>(atoi( argv[3] ) );
  const PixelType outputMaximum = static_cast<PixelType>(atoi( argv[4] ) );
  const ScalarType alpha = atof( argv[5] );
  const ScalarType beta  = atof( argv[6] );

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  typedef itk::SigmoidImageFilter< ImageType, ImageType > FilterType;
  FilterType::Pointer sigmoidFilter = FilterType::New();
  sigmoidFilter->SetInput( reader->GetOutput() );
  sigmoidFilter->SetOutputMinimum( outputMinimum );
  sigmoidFilter->SetOutputMaximum( outputMaximum );
  sigmoidFilter->SetAlpha( alpha );
  sigmoidFilter->SetBeta( beta );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( sigmoidFilter->GetOutput() );

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
