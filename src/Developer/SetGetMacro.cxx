#include "itkImage.h"

#include "ImageFilterX.h"

int
main()
{
  // Setup types
  using ImageType = itk::Image<unsigned char, 2>;
  using FilterType = itk::ImageFilter<ImageType>;

  // Create and the filter
  FilterType::Pointer filter = FilterType::New();
  filter->Update();

  return EXIT_SUCCESS;
}
