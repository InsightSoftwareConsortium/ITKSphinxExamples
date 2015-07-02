#include "itkCovariantVector.h"

int main( int, char* [] )
{
  const unsigned int Dimension = 3;
  typedef double CoordType;

  typedef itk::CovariantVector< CoordType, Dimension > VectorType;

  VectorType u;
  u[0] = -1.;
  u[1] = 1.;
  u[2] = -1.;

  VectorType v;
  v[0] = 1.;
  v[1] = 2.;
  v[2] = 3.;

  std::cout << "u :" << u << std::endl;
  std::cout << "v :" << v << std::endl;
  std::cout << "DotProduct( u, v ) = " << u * v << std::endl;
  std::cout << "u - ( u * v ) * v = " << u - ( u * v ) * v << std::endl;

  return EXIT_SUCCESS;
}
