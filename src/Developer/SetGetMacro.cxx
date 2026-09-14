#include "itkImage.h"

#include "itkImageFilterX.h"

int
main()
{
  // Setup types
  using ImageType = itk::Image<unsigned char, 2>;
  using FilterType = itk::ImageFilterX<ImageType>;

  // Create and the filter
  auto filter = FilterType::New();
  filter->Update();

  return EXIT_SUCCESS;
}
