#include "itkIndex.h"

int main(int, char *[])
{
  const unsigned int Dimension = 2;

  typedef itk::Index< Dimension > IndexType;

  IndexType index;

  // Method 1
  // set both index[0] and index[1] to the same value (in this case, 0).
  index.Fill(0);
  std::cout << index << std::endl;

  // Method 2
  // set each component of the index individually.
  index[0] = 1;
  index[1] = 2;

  std::cout << index << std::endl;

  return EXIT_SUCCESS;
}
