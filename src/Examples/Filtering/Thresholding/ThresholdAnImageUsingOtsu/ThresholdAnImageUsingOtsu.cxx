#include "itkImageFileReader.h"
#include "itkOtsuMultipleThresholdsImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkImageFileWriter.h"

int main( int argc, char* argv[] )
{
  if( argc < 6 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << std::endl;
    std::cerr << " <InputImage> <OutputImage> <NumberOfBins>";
    std::cerr << " <NumberOfThresholds> <LabelOffset>"
              << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef  unsigned char  PixelType;

  typedef itk::Image< PixelType, Dimension >  ImageType;

  typedef itk::ImageFileReader< ImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  typedef itk::OtsuMultipleThresholdsImageFilter< ImageType, ImageType >
    FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetNumberOfHistogramBins( atoi( argv[3] ) );
  filter->SetNumberOfThresholds( atoi( argv[4] ) );
  filter->SetLabelOffset( atoi( argv[5] ) );
  filter->Update();

  FilterType::ThresholdVectorType thresholds = filter->GetThresholds();

  std::cout << "Thresholds:" << std::endl;

  for( size_t i = 0; i < thresholds.size(); i++ )
    {
    std:: cout << thresholds[i] << std::endl;
    }

  std::cout << std::endl;

  typedef itk::RescaleIntensityImageFilter< ImageType, ImageType > RescaleType;
  RescaleType::Pointer rescaler = RescaleType::New();
  rescaler->SetInput( filter->GetOutput() );
  rescaler->SetOutputMinimum( 0 );
  rescaler->SetOutputMaximum( 255 );
  rescaler->Update();

  typedef itk::ImageFileWriter< ImageType >  WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[2] );
  writer->SetInput( rescaler->GetOutput() );
  writer->Update();

  return EXIT_SUCCESS;
}
