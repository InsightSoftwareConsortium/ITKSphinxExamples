#include "itkImage.h"
#include "itkShapedNeighborhoodIterator.h"
#include "itkImageRegionIterator.h"
#include "itkNeighborhoodAlgorithm.h"

int main(int, char*[])
{
  const unsigned int Dimension = 2;

  // Notice that char type pixel values will not appear
  // properly on the command prompt therefore for the
  // demonstration purposes it is best to use the int
  // type, however in real applications iterators have
  // no problems with char type images.
  //typedef itk::Image<unsigned char, 2>  ImageType;
  typedef unsigned int PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;

  ImageType::Pointer image = ImageType::New();

  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(10);

  ImageType::RegionType region(start,size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  typedef itk::ShapedNeighborhoodIterator<ImageType> IteratorType;
  IteratorType::RadiusType radius;
  radius.Fill(1);

  IteratorType iterator(radius, image, image->GetLargestPossibleRegion());
  std::cout << "By default there are " << iterator.GetActiveIndexListSize()
            << " active indices." << std::endl;

  IteratorType::OffsetType top = {{0,-1}};
  iterator.ActivateOffset(top);
  IteratorType::OffsetType bottom = {{0,1}};
  iterator.ActivateOffset(bottom);

  std::cout << "Now there are " << iterator.GetActiveIndexListSize()
            << " active indices." << std::endl;

  IteratorType::IndexListType indexList = iterator.GetActiveIndexList();
  IteratorType::IndexListType::const_iterator
    listIterator = indexList.begin();
  while (listIterator != indexList.end())
    {
    std::cout << *listIterator << " ";
    ++listIterator;
    }
  std::cout << std::endl;

  // Note that ZeroFluxNeumannBoundaryCondition is used by default so even
  // pixels outside of the image will have valid values (equivalent to
  // their neighbors just inside the image)
  for( iterator.GoToBegin(); !iterator.IsAtEnd(); ++iterator )
    {
    std::cout << "New position: " << std::endl;
    IteratorType::ConstIterator ci = iterator.Begin();

    while( !ci.IsAtEnd() )
      {
      std::cout << "Centered at " << iterator.GetIndex() << std::endl;
      std::cout << "Neighborhood index " << ci.GetNeighborhoodIndex()
                << " is offset " << ci.GetNeighborhoodOffset()
                << " and has value " << ci.Get()
                << " The real index is "
                << iterator.GetIndex() + ci.GetNeighborhoodOffset()
                << std::endl;
      ++ci;
      }
    }

  std::cout << std::endl;

  return EXIT_SUCCESS;
}
