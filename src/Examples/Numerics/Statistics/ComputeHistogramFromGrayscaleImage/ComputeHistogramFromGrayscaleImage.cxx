#include "itkImage.h"
#include "itkImageToHistogramFilter.h"
#include "itkImageRandomIteratorWithIndex.h"

typedef itk::Image<unsigned char, 2> ImageType;

void CreateImage(ImageType::Pointer image);

int main(int, char *[])
{
  const unsigned int MeasurementVectorSize = 1; // Grayscale
  const unsigned int binsPerDimension = 30;

  ImageType::Pointer image = ImageType::New();
  CreateImage(image);

  typedef itk::Statistics::ImageToHistogramFilter< ImageType >
    ImageToHistogramFilterType;

  ImageToHistogramFilterType::HistogramType::MeasurementVectorType
    lowerBound(binsPerDimension);
  lowerBound.Fill(0);

  ImageToHistogramFilterType::HistogramType::MeasurementVectorType
    upperBound(binsPerDimension);
  upperBound.Fill(255) ;

  ImageToHistogramFilterType::HistogramType::SizeType
    size(MeasurementVectorSize);
  size.Fill(binsPerDimension);

  ImageToHistogramFilterType::Pointer imageToHistogramFilter =
    ImageToHistogramFilterType::New();
  imageToHistogramFilter->SetInput(image);
  imageToHistogramFilter->SetHistogramBinMinimum(lowerBound);
  imageToHistogramFilter->SetHistogramBinMaximum(upperBound);
  imageToHistogramFilter->SetHistogramSize(size);
  imageToHistogramFilter->Update();

  ImageToHistogramFilterType::HistogramType* histogram =
    imageToHistogramFilter->GetOutput();

  std::cout << "Frequency = ";
  for(unsigned int i = 0; i < histogram->GetSize()[0]; ++i)
    {
    std::cout << histogram->GetFrequency(i) << " ";
    }

  std::cout << std::endl;

  return EXIT_SUCCESS;
}

void CreateImage(ImageType::Pointer image)
{
  // Create a black image with a red square and a green square.
  // This should produce a histogram with very strong spikes.
  itk::Size<2> size;
  size.Fill(10);

  itk::Index<2> start;
  start.Fill(0);

  itk::ImageRegion<2> region(start, size);

  image->SetRegions(region);
  image->Allocate();

  image->FillBuffer(0);

  itk::ImageRandomIteratorWithIndex< ImageType >
    imageIterator( image, image->GetLargestPossibleRegion() );
  imageIterator.SetNumberOfSamples(10);

  while(!imageIterator.IsAtEnd())
    {
    imageIterator.Set(122);
    ++imageIterator;
    }
}
