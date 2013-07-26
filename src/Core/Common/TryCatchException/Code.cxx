#include "itkImage.h"
#include "itkImageFileReader.h"

int main(int, char *[])
{
  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef itk::Image< PixelType, Dimension >  ImageType;
  typedef itk::ImageFileReader< ImageType >   ReaderType;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( "nofile.png" );

  try
    {
    reader->Update();
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;

    // Since the goal of the example is to catch the exception,
    // we declare this a success.
    return EXIT_SUCCESS;
    }

  // Since the goal of the example is to catch the exception,
  // the example fails if it is not caught.
  return EXIT_FAILURE;
}
