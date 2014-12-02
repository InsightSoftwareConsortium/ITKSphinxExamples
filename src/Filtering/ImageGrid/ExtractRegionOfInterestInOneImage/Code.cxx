#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRegionOfInterestImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 7 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << " <start x> <end x> <start y> <end y>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  const itk::IndexValueType startx =
    static_cast< itk::IndexValueType >( atoi( argv[3] ) );
  const itk::IndexValueType endx =
    static_cast< itk::IndexValueType >( atoi( argv[4] ) );

  const itk::IndexValueType starty =
    static_cast< itk::IndexValueType >( atoi( argv[5] ) );
  const itk::IndexValueType endy =
    static_cast< itk::IndexValueType >( atoi( argv[6] ) );

  const unsigned int Dimension = 2;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  ImageType::IndexType start;
  start[0] = startx;
  start[1] = starty;

  ImageType::IndexType end;
  end[0] = endx;
  end[1] = endy;

  ImageType::RegionType region;
  region.SetIndex( start );
  region.SetUpperIndex( end );

  typedef itk::RegionOfInterestImageFilter< ImageType, ImageType >
    FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetRegionOfInterest( region );

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
