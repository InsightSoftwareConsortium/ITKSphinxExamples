#include "itkImage.h"
#include "itkRandomImageSource.h"
#include "itkImageFileWriter.h"
#include "itkAtanImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 2 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;
  typedef unsigned char InputPixelType;

  typedef itk::Image< InputPixelType, Dimension >  InputImageType;

  InputImageType::SizeType size;
  size.Fill( 100 );

  typedef itk::RandomImageSource< InputImageType > RandomImageSourceType;

  RandomImageSourceType::Pointer randomImageSource =
    RandomImageSourceType::New();
  randomImageSource->SetNumberOfThreads(1); // to produce non-random results
  randomImageSource->SetSize(size);
  randomImageSource->Update();

  typedef float OutputPixelType;
  typedef itk::Image< OutputPixelType, Dimension > OutputImageType;

  typedef itk::AtanImageFilter< InputImageType, OutputImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( randomImageSource->GetOutput() );
  filter->Update();

  typedef itk::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[1] );
  writer->SetInput( filter->GetOutput() );
  writer->Update();

  return EXIT_SUCCESS;
}
