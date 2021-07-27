#include "itkImage.h"
#include "itkImageFileReader.h"

#include "itkOilPaintingImageFilter.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " inputFile [bins [radius]]" << std::endl;
    return EXIT_FAILURE;
  }
  unsigned int numberOfBins = 50;
  if (argc > 3)
  {
    numberOfBins = std::stoi(argv[2]);
  }

  unsigned int radius = 2;
  if (argc > 4)
  {
    radius = std::stoi(argv[3]);
  }

  using ImageType = itk::Image<unsigned char, 2>;
  using FilterType = itk::OilPaintingImageFilter<ImageType>;

  const auto input = itk::ReadImage<ImageType>(argv[1]);

  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(input);
  filter->SetNumberOfBins(numberOfBins);
  filter->SetRadius(radius);
  filter->Update();

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(input, true, itksys::SystemTools::GetFilenameName(reader->GetFileName()));

  std::stringstream desc;
  desc << "OilPaintingImageFilter, bins = " << numberOfBins << " radius = " << radius;
  viewer.AddImage(filter->GetOutput(), true, desc.str());

  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}
