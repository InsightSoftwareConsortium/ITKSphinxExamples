#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkGradientMagnitudeImageFilter.h"

int main(int argc, char * argv[])
{
  // Verify command line arguments
  if( argc != 3 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " <InputImage> <OutputImage" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef unsigned char                           InputPixelType;
  typedef itk::Image< InputPixelType, Dimension > InputImageType;

  typedef float                                      OutputPixelType;
  typedef itk::Image< OutputPixelType, Dimension >   OutputImageType;

  // Create and setup a reader
  typedef itk::ImageFileReader< InputImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  // Create and setup a gradient filter
  typedef itk::GradientMagnitudeImageFilter<
		  InputImageType, OutputImageType >  FilterType;

  FilterType::Pointer gradientFilter = FilterType::New();
  gradientFilter->SetInput( reader->GetOutput() );
  gradientFilter->Update();

  typedef itk::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[2] );
  writer->SetInput( gradientFilter->GetOutput() );
  writer->Update();

  return EXIT_SUCCESS;
}
