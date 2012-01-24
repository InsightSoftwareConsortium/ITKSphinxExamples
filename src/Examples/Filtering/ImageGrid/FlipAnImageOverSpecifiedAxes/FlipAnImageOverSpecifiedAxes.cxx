#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkFlipImageFilter.h"

int main(int argc, char* argv[])
{
  if( argc != 3 )
    {
    std::cerr << "Usage: " << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned Dimension = 2;

  typedef unsigned char                       PixelType;
  typedef itk::Image< PixelType, Dimension >  ImageType;

  typedef itk::ImageFileReader< ImageType >   ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  typedef itk::FlipImageFilter< ImageType >   FlipImageFilterType;

  FlipImageFilterType::Pointer flipFilter
          = FlipImageFilterType::New ();
  flipFilter->SetInput( reader->GetOutput() );

  FlipImageFilterType::FlipAxesArrayType flipAxes;
  flipAxes[0] = false;
  flipAxes[1] = true;

  flipFilter->SetFlipAxes(flipAxes);
  flipFilter->Update();

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[2] );
  writer->SetInput( flipFilter->GetOutput() );
  writer->Update();

  return EXIT_SUCCESS;
}

