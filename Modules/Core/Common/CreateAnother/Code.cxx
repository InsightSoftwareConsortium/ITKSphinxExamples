#include "itkAbsImageFilter.h"
#include "itkImage.h"

template< class TImage >
void CreateImage(typename TImage::Pointer image)
{
  typedef TImage ImageType;
  typename ImageType::IndexType start;
  start.Fill(0);

  typename ImageType::SizeType size;
  size.Fill(2);

  typename ImageType::RegionType region(start,size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer( -2 );
}

int main(int, char*[])
{
  const unsigned int Dimension = 2;
  typedef double PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::AbsImageFilter<ImageType, ImageType> FilterType;
  FilterType::Pointer filter = FilterType::New();
  FilterType::Pointer filter2 =
    dynamic_cast<FilterType*>(filter->CreateAnother().GetPointer());

  ImageType::Pointer image = ImageType::New();
  CreateImage< ImageType >(image);

  filter2->SetInput(image);
  filter2->Update();

  itk::Index< Dimension > index;
  index.Fill(0);

  std::cout << filter2->GetOutput()->GetPixel(index) << std::endl;

  return EXIT_SUCCESS;
}
