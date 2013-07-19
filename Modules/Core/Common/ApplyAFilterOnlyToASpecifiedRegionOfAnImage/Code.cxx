#include "itkImage.h"
#include "itkRandomImageSource.h"
#include "itkDerivativeImageFilter.h"

int main(int, char *[])
{
  const unsigned int Dimension = 2;
  typedef float PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  ImageType::SizeType smallSize;
  smallSize.Fill(10);

  ImageType::IndexType index;
  index.Fill(0);

  ImageType::RegionType region(index, smallSize);

  ImageType::SizeType bigSize;
  bigSize.Fill(10000);

  typedef itk::RandomImageSource<ImageType> RandomSourceType;
  RandomSourceType::Pointer randomImageSource = RandomSourceType::New();
  randomImageSource->SetNumberOfThreads(1); // to produce non-random results
  randomImageSource->SetSize(bigSize);
  randomImageSource->GetOutput()->SetRequestedRegion(smallSize);
  randomImageSource->Update();

  std::cout << "Created random image." << std::endl;

  typedef itk::DerivativeImageFilter<ImageType, ImageType >
    DerivativeImageFilterType;

  DerivativeImageFilterType::Pointer derivativeFilter =
    DerivativeImageFilterType::New();
  derivativeFilter->SetInput( randomImageSource->GetOutput() );
  derivativeFilter->SetDirection(0); // "x" axis
  derivativeFilter->GetOutput()->SetRequestedRegion(smallSize);
  derivativeFilter->Update();

  std::cout << "Computed derivative." << std::endl;

  return EXIT_SUCCESS;
}
