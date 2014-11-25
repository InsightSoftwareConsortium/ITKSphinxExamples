#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkNumericSeriesFileNames.h"
#include "itkImageSeriesWriter.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  std::string format =  std::string( outputFileName ) +
                        std::string( "-%d.png" );

  const unsigned int Dimension = 3;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > InputImageType;

  typedef itk::ImageFileReader< InputImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  typedef unsigned char OutputPixelType;
  typedef itk::Image< OutputPixelType, Dimension > RescaleImageType;

  typedef itk::RescaleIntensityImageFilter< InputImageType, RescaleImageType >
    RescaleFilterType;
  RescaleFilterType::Pointer rescale = RescaleFilterType::New();
  rescale->SetInput( reader->GetOutput() );
  rescale->SetOutputMinimum( 0 );
  rescale->SetOutputMaximum( 255 );
  rescale->UpdateLargestPossibleRegion();

  InputImageType::RegionType region =
    reader->GetOutput()->GetLargestPossibleRegion();
  InputImageType::SizeType size = region.GetSize();

  itk::NumericSeriesFileNames::Pointer fnames =
    itk::NumericSeriesFileNames::New();
  fnames->SetStartIndex( 0 );
  fnames->SetEndIndex( size[2] - 1 );
  fnames->SetIncrementIndex( 1 );
  fnames->SetSeriesFormat( format.c_str() );

  typedef itk::Image< OutputPixelType, 2 > OutputImageType;

  typedef itk::ImageSeriesWriter< RescaleImageType, OutputImageType >
    WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( rescale->GetOutput() );
  writer->SetFileNames( fnames->GetFileNames() );

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
