#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCovariantVector.h"

#include "ImageFilterMultipleInputsDifferentType.h"

int main(int, char*[])
{
  // Setup types
  using VectorImageType = itk::Image<itk::CovariantVector<unsigned char, 3>, 2>;
  using ScalarImageType = itk::Image<unsigned char, 2>;
  using FilterType = itk::ImageFilterMultipleInputsDifferentType<VectorImageType, ScalarImageType>;

  using ReaderType = itk::ImageFileReader<VectorImageType>;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName("Test.jpg");
  reader->Update();

  // Create and the filter
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(reader->GetOutput());
  filter->Update();

  using WriterType = itk::ImageFileWriter< VectorImageType  >;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName("TestOutput.jpg");
  writer->SetInput(filter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}
