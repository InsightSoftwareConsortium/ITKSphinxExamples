#include "itkCovariantVector.h"

int main(int, char*[])
{
  const unsigned int Dimension = 3;
  typedef double CoordType;

  typedef itk::CovariantVector< CoordType, Dimension > VectorType;
  VectorType v;
  v[0] = 1.0;
  v[1] = 2.0;
  v[2] = 3.0;

  std::cout << "v: " << v << std::endl;

  return EXIT_SUCCESS;
}
