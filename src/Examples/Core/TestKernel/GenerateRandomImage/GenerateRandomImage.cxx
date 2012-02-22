#include "itkImage.h"
#include "itkRandomImageSource.h"
#include "itkImageFileWriter.h"

int main(int argc, char* argv[])
{
  if( argc != 2 )
    {
    std::cerr << "Usage:" << std::endl;
    std::cerr << argv[0] << " <OutputFileName>" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;
  typedef unsigned char PixelType;

  typedef itk::Image< PixelType, Dimension >  ImageType;

  ImageType::SizeType size;
  size.Fill(10);

  typedef itk::RandomImageSource< ImageType > RandomImageSourceType;

  RandomImageSourceType::Pointer randomImageSource =
    RandomImageSourceType::New();
  randomImageSource->SetNumberOfThreads(1); // to produce non-random results
  randomImageSource->SetSize(size);
  randomImageSource->Update();

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[1] );
  writer->SetInput( randomImageSource->GetOutput() );
  writer->Update();

  return EXIT_SUCCESS;
}
