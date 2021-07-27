#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCovariantVector.h"

#include "ImageFilterMultipleInputsDifferentType.h"

int
main(int, char *[])
{
  // Setup types
  using VectorImageType = itk::Image<itk::CovariantVector<unsigned char, 3>, 2>;
  using ScalarImageType = itk::Image<unsigned char, 2>;
  using FilterType = itk::ImageFilterMultipleInputsDifferentType<VectorImageType, ScalarImageType>;

  const auto input = itk::ReadImage<VectorImageType>("Test.jpg");

  // Create and the filter
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(input);
  filter->Update();

  itk::WriteImage(filter->GetOutput(), "TestOutput.jpg");

  return EXIT_SUCCESS;
}
