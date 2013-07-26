#include "itkImage.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include "itkTIFFImageIO.h"

int main(int argc, char *argv[])
{
  std::string outputFilename;
  if(argc > 1)
    {
    outputFilename = argv[1];
    }
  else
    {
    outputFilename = "test.tif";
    }

  const unsigned int    Dimension = 2;
  typedef unsigned char PixelType;

  typedef itk::Image< PixelType, Dimension >  ImageType;

  ImageType::RegionType region;
  ImageType::IndexType start;
  start[0] = 0;
  start[1] = 0;

  ImageType::SizeType size;
  size[0] = 200;
  size[1] = 300;

  region.SetSize(size);
  region.SetIndex(start);

  ImageType::Pointer image = ImageType::New();
  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image,region);

  while(!imageIterator.IsAtEnd())
    {
    if(imageIterator.GetIndex()[0] > 100)
      {
      imageIterator.Set(100);
      }
    else
      {
      imageIterator.Set(200);
      }
    ++imageIterator;
    }

  typedef itk::ImageFileWriter< ImageType > WriterType;
  typedef itk::TIFFImageIO                  TIFFIOType;

  TIFFIOType::Pointer tiffIO = TIFFIOType::New();
  tiffIO->SetPixelType(itk::ImageIOBase::SCALAR);

  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(outputFilename);
  writer->SetInput(image);
  writer->SetImageIO(tiffIO);
  writer->Update();

  return EXIT_SUCCESS;
}
