#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkTileImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc < 3 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << "<input1> <input2> <input3> ... <output>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int InputDimension   = 2;
  const unsigned int OutputDimension  = 3;

  typedef unsigned char                             PixelType;
  typedef itk::Image< PixelType, InputDimension >   InputImageType;
  typedef itk::Image< PixelType, OutputDimension >  OutputImageType;

  typedef itk::ImageFileReader< InputImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();

  typedef itk::TileImageFilter< InputImageType, OutputImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();

  itk::FixedArray< unsigned int, OutputImageDimension > layout;
  layout[0] = 2;
  layout[1] = 2;
  layout[2] = 0;

  filter->SetLayout( layout );

  for( int i = 1; i < argc - 1; i++ )
    {
    reader->SetFileName( argv[i] );

    try
      {
      reader->Update();
      }
    catch( itk::ExceptionObject & e )
      {
      std::cerr << e << std::endl;
      return EXIT_FAILURE;
      }

    InputImageType::Pointer input = reader->GetOutput();
    input->DisconnectPipeline();

    filter->SetInput( i - 1, input );
    }

  PixelType defaultValue = 128;

  filter->SetDefaultPixelValue( defaultValue );
  filter->Update();

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[ argc - 1 ] );
  writer->SetInput( filter->GetOutput() );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & e )
    {
    std::cerr << e << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
