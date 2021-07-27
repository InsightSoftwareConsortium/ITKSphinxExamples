#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "ImageFilterMultipleOutputsDifferentType.h"

int
main(int, char *[])
{
  // Setup types
  using InputImageType = itk::Image<unsigned char, 2>;
  using OutputImageType1 = itk::Image<float, 2>;
  using OutputImageType2 = itk::Image<int, 2>;
  using FilterType = itk::ImageFilterMultipleOutputsDifferentType<InputImageType, OutputImageType1, OutputImageType2>;

  // Create and the filter
  FilterType::Pointer filter = FilterType::New();
  filter->Update();

  itk::WriteImage(filter->GetOutput1(), "TestOutput1.jpg");

  itk::WriteImage(filter->GetOutput2(), "TestOutput2.jpg");

  return EXIT_SUCCESS;
}
