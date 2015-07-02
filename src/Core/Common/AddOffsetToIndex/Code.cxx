#include "itkIndex.h"
#include "itkOffset.h"

#include <iostream>

int main(int, char * [])
{
  const unsigned int Dimension = 2;

  itk::Index< Dimension > index;
  index.Fill( 5 );

  itk::Offset< Dimension > offset;
  offset.Fill( 1 );

  std::cout << "index: "          << index << std::endl;
  std::cout << "offset: "         << offset << std::endl;
  std::cout << "index + offset: " << index + offset << std::endl;
  std::cout << std::endl;

  offset[0] = -1;

  std::cout << "index: "          << index << std::endl;
  std::cout << "offset: "         << offset << std::endl;
  std::cout << "index + offset: " << index + offset << std::endl;
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
