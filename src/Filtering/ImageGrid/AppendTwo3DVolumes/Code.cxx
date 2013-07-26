#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkTileImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 4 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName1> <InputFileName2> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }
  const char * inputFileName1 = argv[1];
  const char * inputFileName2 = argv[2];
  const char * outputFileName = argv[3];

  const unsigned int Dimension = 3;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader1 = ReaderType::New();
  reader1->SetFileName( inputFileName1 );

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader2 = ReaderType::New();
  reader2->SetFileName( inputFileName2 );

  typedef itk::TileImageFilter< ImageType, ImageType > TileFilterType;
  TileFilterType::Pointer tileFilter = TileFilterType::New();
  tileFilter->SetInput( 0, reader1->GetOutput() );
  tileFilter->SetInput( 1, reader2->GetOutput() );
  TileFilterType::LayoutArrayType layout;
  layout[0] = 1;
  layout[1] = 1;
  layout[2] = 2;
  tileFilter->SetLayout( layout );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( tileFilter->GetOutput() );
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
