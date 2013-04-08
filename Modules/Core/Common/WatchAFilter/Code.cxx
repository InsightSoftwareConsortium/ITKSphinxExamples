#include "itkImage.h"
#include "itkSimpleFilterWatcher.h"
#include "itkThresholdImageFilter.h"
#include "itkImageRegionIterator.h"

template< class TImage >
void CreateImage(typename TImage::Pointer image)
{
  typedef TImage ImageType;

  // Create an image with 2 connected components
  typename ImageType::RegionType region;
  typename ImageType::IndexType start;
  start.Fill( 0 );

  typename ImageType::SizeType size;
  size.Fill( 100 );

  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator< ImageType > imageIterator(image,region);

  while(!imageIterator.IsAtEnd())
    {
    imageIterator.Set(255);
    ++imageIterator;
    }

}
int main(int, char *[])
{
  const unsigned int Dimension = 2;
  typedef unsigned char PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  ImageType::Pointer image = ImageType::New();
  CreateImage< ImageType >(image);

  typedef itk::ThresholdImageFilter <ImageType>
          ThresholdImageFilterType;

  ThresholdImageFilterType::Pointer thresholdFilter
          = ThresholdImageFilterType::New();
  thresholdFilter->SetInput(image);
  thresholdFilter->ThresholdBelow(100);
  thresholdFilter->SetOutsideValue(0);

  itk::SimpleFilterWatcher watcher(thresholdFilter, "ThresholdFilter");

  thresholdFilter->Update();

  return EXIT_SUCCESS;
}
