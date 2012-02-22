#include "itkImageRegion.h"
#include "itkIndex.h"
#include "itkSize.h"

int main(int, char *[])
{
  const unsigned int Dimension = 2;

  typedef itk::ImageRegion< Dimension > RegionType;
  typedef RegionType::SizeType          SizeType;
  typedef RegionType::IndexType         IndexType;

  SizeType size;
  size.Fill(3);

  IndexType start;
  start.Fill(0);

  RegionType region(start,size);

  IndexType testPixel1;
  testPixel1[0] = 1;
  testPixel1[1] = 1;

  IndexType testPixel2;
  testPixel2[0] = 6;
  testPixel2[1] = 6;

  std::cout << testPixel1 << " ";

  if( region.IsInside(testPixel1) )
    {
    std::cout << "Inside";
    }
  else
    {
    std::cout << "Outside";
    return EXIT_FAILURE;
    }
  std::cout << std::endl;

  std::cout << testPixel2 << " ";
  if( region.IsInside(testPixel2) )
    {
    std::cout << "Inside";
    return EXIT_FAILURE;
    }
  else
    {
    std::cout << "Outside";
    }
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
