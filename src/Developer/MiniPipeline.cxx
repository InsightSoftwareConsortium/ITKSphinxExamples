#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "ImageFilterY.h"

template <typename TImage>
static void CreateImage(TImage* const image);

int main(int, char*[])
{
  // Setup types
  using ImageType = itk::Image<unsigned char, 2>;
  using FilterType = itk::ImageFilter<ImageType>;

  ImageType::Pointer image = ImageType::New();
  CreateImage(image.GetPointer());

  std::cout << "Input:" << std::endl;
  std::cout << image->GetLargestPossibleRegion() << std::endl;
  // Create and the filter
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(image);
  filter->Update();

  std::cout << "Input:" << std::endl;
  std::cout << filter->GetOutput()->GetLargestPossibleRegion() << std::endl;
  
  using WriterType = itk::ImageFileWriter< ImageType  >;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName("Output.png");
  writer->SetInput(filter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}

template <typename TImage>
void CreateImage(TImage* const image)
{
  // Create an image with 2 connected components
  typename TImage::IndexType corner = {{0,0}};

  unsigned int NumRows = 200;
  unsigned int NumCols = 300;
  typename TImage::SizeType size = {{NumRows, NumCols}};

  typename TImage::RegionType region(corner, size);

  image->SetRegions(region);
  image->Allocate();

  // Make another square
  for(unsigned int r = 40; r < 100; r++)
  {
    for(unsigned int c = 40; c < 100; c++)
    {
      typename TImage::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 15);
    }
  }
}
