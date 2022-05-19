#include "itkImage.h"

#include "ImageFilterMultipleInputs.h"

int
main(int, char *[])
{
  // Setup types
  using ImageType = itk::Image<unsigned char, 2>;
  using FilterType = itk::ImageFilterMultipleInputs<ImageType>;

  auto image = ImageType::New();
  auto mask = ImageType::New();

  // Create and the filter
  auto filter = FilterType::New();
  filter->SetInputImage(image);
  filter->SetInputMask(mask);
  filter->Update();

  return EXIT_SUCCESS;
}
