#include "itkImageRegion.h"

int main(int, char *[])
{
  const unsigned int Dimension = 2;

  typedef itk::ImageRegion< Dimension > RegionType;
  RegionType::SizeType size;
  size.Fill(3);

  RegionType::IndexType index;
  index.Fill(1);

  RegionType region( index, size );

  std::cout << region << std::endl;

  return EXIT_SUCCESS;
}
