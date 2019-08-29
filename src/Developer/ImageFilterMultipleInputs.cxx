#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "ImageFilterMultipleInputs.h"

int
main(int, char *[])
{
  // Setup types
  using ImageType = itk::Image<unsigned char, 2>;
  using FilterType = itk::ImageFilterMultipleInputs<ImageType>;

  ImageType::Pointer image = ImageType::New();
  ImageType::Pointer mask = ImageType::New();

  // Create and the filter
  FilterType::Pointer filter = FilterType::New();
  filter->SetInputImage(image);
  filter->SetInputMask(mask);
  filter->Update();

  return EXIT_SUCCESS;
}
