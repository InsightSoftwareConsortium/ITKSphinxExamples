#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "MultiThreadedImageFilter.h"

template <typename TImage>
static void
CreateImage(TImage * const image);

template <typename TImage>
static void
OutputImage(TImage * const image);

int
main(int, char *[])
{
  // Setup types
  using ImageType = itk::Image<int, 2>;
  using FilterType = itk::MultiThreadedImageFilter<ImageType>;

  ImageType::Pointer image = ImageType::New();
  CreateImage(image.GetPointer());

  // Create and the filter
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(image);
  // filter->SetNumberOfThreads(3); // There is no need to specify this, it is automatically determined
  filter->Update();

  std::cout << "Image after filter: " << std::endl;
  OutputImage(image.GetPointer());

  std::cout << "Output: " << std::endl;
  OutputImage(filter->GetOutput());

  return EXIT_SUCCESS;
}


template <typename TImage>
void
CreateImage(TImage * const image)
{
  // Create an image with 2 connected components
  typename TImage::IndexType corner = { { 0, 0 } };

  //   unsigned int NumRows = 200;
  //   unsigned int NumCols = 300;

  unsigned int              NumRows = 3;
  unsigned int              NumCols = 2;
  typename TImage::SizeType size = { { NumRows, NumCols } };

  typename TImage::RegionType region(corner, size);

  image->SetRegions(region);
  image->Allocate();

  image->FillBuffer(0);
}

template <typename TImage>
void
OutputImage(TImage * const image)
{
  itk::ImageRegionConstIterator<TImage> imageIterator(image, image->GetLargestPossibleRegion());

  while (!imageIterator.IsAtEnd())
  {
    std::cout << imageIterator.Get() << std::endl;

    ++imageIterator;
  }
}
