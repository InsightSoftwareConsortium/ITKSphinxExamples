#include "itkSize.h"

int main(int, char *[])
{
  const unsigned int Dimension = 2;
  itk::Size< Dimension > size;

  // Method 1
  // set both components (size[0] and size[1]) to the same value
  // (in this case, 0).
  size.Fill(0);
  std::cout << size << std::endl;

  // Method 2
  // set each component separately.
  size[0] = 1;
  size[1] = 2;

  std::cout << size << std::endl;

  return EXIT_SUCCESS;
}
