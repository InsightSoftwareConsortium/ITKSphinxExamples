#include "itkImage.h"

#include "ImageSource.h"

int
main()
{
  // Setup types
  using ImageType = itk::Image<unsigned char, 2>;
  ImageType::Pointer image = ImageType::New();

  // Create and the filter
  using FilterType = itk::ImageFilter<ImageType>;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(image);
  filter->Update();

  return EXIT_SUCCESS;
}
