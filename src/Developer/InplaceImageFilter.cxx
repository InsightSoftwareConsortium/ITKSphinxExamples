#include "itkImage.h"

#include "MyInPlaceImageFilter.h"

template <typename TImage>
static void
CreateImage(TImage * const image);

int
main(int, char *[])
{
  // Setup types
  using ImageType = itk::Image<int, 2>;
  using FilterType = itk::MyInPlaceImageFilter<ImageType>;

  ImageType::Pointer image = ImageType::New();
  CreateImage(image.GetPointer());

  // Create and the filter
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(image);
  filter->SetInPlace(true);
  filter->Update();

  itk::Index<2> cornerPixel = image->GetLargestPossibleRegion().GetIndex();

  // The output here should be "3"
  std::cout << "Filter output:" << std::endl;
  std::cout << filter->GetOutput()->GetPixel(cornerPixel) << std::endl;

  // The follow calls fail. This is because the output has stolen the input's
  // buffer and the input has no image buffer.
  //   std::cout << "Image output:" << std::endl;
  //   std::cout << image->GetPixel(cornerPixel) << std::endl;

  return EXIT_SUCCESS;
}


template <typename TImage>
void
CreateImage(TImage * const image)
{
  // Create an image with 2 connected components
  typename TImage::IndexType corner = { { 0, 0 } };

  unsigned int              NumRows = 200;
  unsigned int              NumCols = 300;
  typename TImage::SizeType size = { { NumRows, NumCols } };

  typename TImage::RegionType region(corner, size);

  image->SetRegions(region);
  image->Allocate();

  image->FillBuffer(0);
}
