#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 5 )
  {
  std::cerr << "Usage: "<< std::endl;
  std::cerr << argv[0];
  std::cerr << "<InputFileName> <OutputFileName> <OutputMin> <OutputMax>";
  std::cerr << std::endl;
  return EXIT_FAILURE;
  }

  const unsigned int Dimension = 2;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  typedef itk::RescaleIntensityImageFilter< ImageType, ImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetOutputMinimum( atoi( argv[3] ) );
  filter->SetOutputMaximum( atoi( argv[4] ) );
  filter->Update();

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[2] );
  writer->SetInput( filter->GetOutput() );
  writer->Update();

  return EXIT_SUCCESS;
}
