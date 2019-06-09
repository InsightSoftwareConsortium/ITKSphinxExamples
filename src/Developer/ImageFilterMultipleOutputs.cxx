#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "ImageFilterMultipleOutputs.h"

int main(int, char*[])
{
  // Setup types
  using ImageType = itk::Image<unsigned char, 2>;
  using FilterType = itk::ImageFilterMultipleOutputs<ImageType>;

  // Create and the filter
  FilterType::Pointer filter = FilterType::New();
  filter->Update();

  {
  using WriterType = itk::ImageFileWriter< ImageType  >;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName("TestOutput1.jpg");
  writer->SetInput(filter->GetOutput1());
  writer->Update();
  }
  
  {
  using WriterType = itk::ImageFileWriter< ImageType  >;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName("TestOutput2.jpg");
  writer->SetInput(filter->GetOutput2());
  writer->Update();
  }
  
  return EXIT_SUCCESS;
}
