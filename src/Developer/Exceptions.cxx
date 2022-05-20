#include "itkImage.h"

#include "ImageSource.h"

int
main()
{
  // Setup types
  using ImageType = itk::Image<unsigned char, 2>;
  auto image = ImageType::New();

  // Create and the filter
  using FilterType = itk::ImageFilter<ImageType>;
  auto filter = FilterType::New();
  filter->SetInput(image);
  filter->Update();

  return EXIT_SUCCESS;
}
