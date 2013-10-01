#include "itkImageSeriesReader.h"
#include "itkNumericSeriesFileNames.h"

int main( int argc, char* argv[] )
{
  if( argc != 4 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <seriesFormat> <startIndex> <endIndex>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * seriesFormat = argv[1];
  unsigned int startIndex = atoi( argv[2] );
  unsigned int endIndex = atoi( argv[3] );

  const unsigned int Dimension = 3;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::NumericSeriesFileNames NameGeneratorType;
  NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();
  nameGenerator->SetSeriesFormat( seriesFormat );
  nameGenerator->SetStartIndex( 0 );
  nameGenerator->SetEndIndex( 2 );
  std::vector< std::string > fileNames = nameGenerator->GetFileNames();

  typedef itk::ImageSeriesReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileNames( fileNames );

  try
    {
    reader->Update();

    ImageType::ConstPointer output = reader->GetOutput();
    const ImageType::RegionType largestRegion =
      output->GetLargestPossibleRegion();
    std::cout << "Initial LargestPossibleRegion: ";
    std::cout << largestRegion << std::endl;;
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  fileNames.pop_back();

  try
    {
    std::cout << "\nTrying to call Update() "
              << "after shrinking the LargestPossibleRegion...\n" << std::endl;
    reader->SetFileNames( fileNames );
    reader->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    // Print out the error that occurs
    std::cout << "Error: " << error << std::endl;
    }

  try
    {
    std::cout << "Trying to call UpdateLargestPossibleRegion() "
              << "after shrinking the LargestPossibleRegion...\n" << std::endl;
    reader->SetFileNames( fileNames );
    reader->UpdateLargestPossibleRegion();

    ImageType::ConstPointer output = reader->GetOutput();
    const ImageType::RegionType largestRegion =
      output->GetLargestPossibleRegion();
    std::cout << "Shrunk LargestPossibleRegion: ";
    std::cout << largestRegion << std::endl;;
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
