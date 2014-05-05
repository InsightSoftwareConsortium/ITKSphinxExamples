#include "itkMeanImageFilter.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main(int argc, char * argv[])
{
  if( argc != 4 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " <InputImageFile> <OutputImageFile> <radius>"
              << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];
  const int radiusValue = atoi( argv[3] );

  typedef unsigned char                       PixelType;
  typedef itk::Image< PixelType, Dimension >  ImageType;

  typedef itk::ImageFileReader< ImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  typedef itk::MeanImageFilter< ImageType, ImageType >  FilterType;
  FilterType::Pointer meanFilter = FilterType::New();

  FilterType::InputSizeType radius;
  radius.Fill( radiusValue );

  meanFilter->SetRadius( radius );
  meanFilter->SetInput( reader->GetOutput() );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( meanFilter->GetOutput() );
  writer->SetFileName( outputFileName );

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
