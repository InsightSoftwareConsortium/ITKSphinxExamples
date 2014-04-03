#include "itkImageFileReader.h"
#include "itkMetaImageIOFactory.h"
#include "itkPNGImageIOFactory.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 )
     {
     std::cerr << "Usage: "<< std::endl;
     std::cerr << argv[0];
     std::cerr << " <MetaImageFileName> <PNGFileName>";
     std::cerr << std::endl;
     return EXIT_FAILURE;
     }

  const char * metaImageFileName = argv[1];
  const char * pngFileName = argv[2];

  const unsigned int Dimension = 2;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();

  typedef std::list< itk::LightObject::Pointer > RegisteredObjectsContainerType;


  RegisteredObjectsContainerType registeredIOs =
    itk::ObjectFactoryBase::CreateAllInstance( "itkImageIOBase" );
  std::cout << "When CMake is not used to register the IO classes, there are\n"
            << registeredIOs.size()
            << " IO objects available to the ImageFileReader.\n" << std::endl;


  std::cout << "When we try to read a MetaImage, we will ";
  reader->SetFileName( metaImageFileName );
  try
    {
    reader->Update();
    return EXIT_FAILURE;
    }
  catch( itk::ImageFileReaderException & )
    {
    std::cout << "fail.\n" << std::endl;
    }


  std::cout << "After registering the MetaImageIO object, ";
  itk::MetaImageIOFactory::RegisterOneFactory();

  std::cout << "there are\n";
  registeredIOs = itk::ObjectFactoryBase::CreateAllInstance( "itkImageIOBase" );
  std::cout << registeredIOs.size()
            << " IO objects available to the ImageFileReader.\n" << std::endl;

  std::cout << "Now, when we try to read a MetaImage, we will ";
  try
    {
    reader->Update();
    std::cout << "succeed.\n" << std::endl;
    }
  catch( itk::ImageFileReaderException & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }


  std::cout << "Every format desired to be supported by the reader\n"
            << "must be registered." << std::endl;
  itk::PNGImageIOFactory::RegisterOneFactory();
  reader->SetFileName( pngFileName );
  try
    {
    reader->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }


  return EXIT_SUCCESS;
}
