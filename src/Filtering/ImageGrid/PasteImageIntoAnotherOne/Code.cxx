#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkPasteImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 6 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <SourceFileName> <DestinationFileName> <OutputFileName> <start x> <start y>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * sourceFileName       = argv[1];
  const char * destinationFileName  = argv[2];
  const char * outputFileName       = argv[3];

  int startX = atoi( argv[4] );
  int startY = atoi( argv[5] );

  const unsigned int Dimension = 2;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  ImageType::IndexType index;
  index[0] = startX;
  index[1] = startY;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer sourceReader = ReaderType::New();
  sourceReader->SetFileName( sourceFileName );
  sourceReader->Update();

  ReaderType::Pointer destinationReader = ReaderType::New();
  destinationReader->SetFileName( destinationFileName );

  typedef itk::PasteImageFilter< ImageType, ImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetSourceImage( sourceReader->GetOutput() );
  filter->SetSourceRegion( sourceReader->GetOutput()->GetLargestPossibleRegion() );
  filter->SetDestinationImage( destinationReader->GetOutput() );
  filter->SetDestinationIndex( index );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( filter->GetOutput() );
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
