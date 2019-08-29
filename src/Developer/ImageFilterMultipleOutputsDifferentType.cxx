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

  {
    using WriterType = itk::ImageFileWriter<OutputImageType1>;
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName("TestOutput1.jpg");
    writer->SetInput(filter->GetOutput1());
    writer->Update();
  }

  {
    using WriterType = itk::ImageFileWriter<OutputImageType2>;
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName("TestOutput2.jpg");
    writer->SetInput(filter->GetOutput2());
    writer->Update();
  }

  return EXIT_SUCCESS;
}
