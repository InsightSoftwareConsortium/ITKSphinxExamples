#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMultiplyImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 4 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <Factor> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const double factor = atof( argv[2] );
  const char * outputFileName = argv[3];
  const unsigned int Dimension = 2;

  typedef unsigned char                           InputPixelType;
  typedef itk::Image< InputPixelType, Dimension > InputImageType;

  typedef itk::ImageFileReader< InputImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  typedef double                                    OutputPixelType;
  typedef itk::Image< OutputPixelType, Dimension >  OutputImageType;

  typedef itk::MultiplyImageFilter< InputImageType, InputImageType, OutputImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetConstant( factor );

  typedef itk::ImageFileWriter< OutputImageType > WriterType;
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
