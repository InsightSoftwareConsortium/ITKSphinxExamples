#include "itkImage.h"
#include "itkImageFileWriter.h"

int main(int argc, char* argv[])
{
  if( argc != 2 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " <OutputFileName>" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;
  typedef unsigned char PixelType;

  typedef itk::Image< PixelType, Dimension >  ImageType;

  ImageType::RegionType region;

  ImageType::IndexType start;
  start.Fill( 0 );

  region.SetIndex(start);

  ImageType::SizeType size;
  size[0] = 200;
  size[1] = 300;

  region.SetSize(size);

  ImageType::Pointer image = ImageType::New();
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer( itk::NumericTraits< PixelType >::Zero );

  ImageType::IndexType pixelIndex;

  for(ImageType::IndexValueType r = 0; r < 50; r++)
    {
    pixelIndex[0] = 4 * r;
    pixelIndex[1] = 4 * r;

    image->SetPixel(pixelIndex, 128);

    pixelIndex[0] = 4 * r;
    pixelIndex[1] = 200 - 4 * r;

    image->SetPixel(pixelIndex, 255);
    }

  for(ImageType::IndexValueType r = 0; r < 25; r++)
    {
    pixelIndex[0] = 8 * r;
    pixelIndex[1] = 200 + 4 * r;

    image->SetPixel(pixelIndex, 128);

    pixelIndex[0] = 8 * r;
    pixelIndex[1] = 250;

    image->SetPixel(pixelIndex, 180 );
    }

  pixelIndex[0] = 95;
  pixelIndex[1] = 150;

  image->SetPixel( pixelIndex, 200 );

  pixelIndex[0] = 100;
  pixelIndex[1] = 150;

  image->SetPixel( pixelIndex, 200 );

  pixelIndex[0] = 105;
  pixelIndex[1] = 150;

  image->SetPixel( pixelIndex, 200 );

  pixelIndex[0] = 100;
  pixelIndex[1] = 155;

  image->SetPixel( pixelIndex, 200 );

  pixelIndex[0] = 100;
  pixelIndex[1] = 145;

  image->SetPixel( pixelIndex, 200 );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( image );
  writer->SetFileName( argv[1] );

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
