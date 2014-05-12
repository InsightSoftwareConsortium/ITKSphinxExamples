#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkVotingBinaryIterativeHoleFillingImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 6 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> <radius> <majority threshold> <number of iterations>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  int r = atoi( argv[3] );
  int majorityThreshold = atoi( argv[4] );
  unsigned int numberOfIterations = atoi( argv[5] );

  const unsigned int Dimension = 2;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  typedef itk::VotingBinaryIterativeHoleFillingImageFilter< ImageType > FilterType;
  FilterType::InputSizeType radius;
  radius.Fill( r );

  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetRadius( radius );
  filter->SetMajorityThreshold( majorityThreshold );
  filter->SetBackgroundValue( itk::NumericTraits< PixelType >::Zero );
  filter->SetForegroundValue( itk::NumericTraits< PixelType >::max() );
  filter->SetMaximumNumberOfIterations( numberOfIterations );

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
