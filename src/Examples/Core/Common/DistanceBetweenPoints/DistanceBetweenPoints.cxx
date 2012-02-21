#include "itkPoint.h"
#include "vnl/vnl_math.h"

#include <iostream>

int main(int, char *[])
{
  const unsigned int Dimension = 3;
  typedef double CoordType;

  typedef itk::Point< CoordType, Dimension > PointType;

  PointType p0;
  p0[0] = 0.0;
  p0[1] = 0.0;
  p0[2] = 0.0;

  PointType p1;
  p1[0] = 1.0;
  p1[1] = 1.0;
  p1[2] = 1.0;

  PointType::RealType dist = p0.EuclideanDistanceTo(p1);
  std::cout << "Dist: " << dist << std::endl;

  if( dist != p1.EuclideanDistanceTo(p0) )
    {
    std::cerr << "p0.EuclideanDistanceTo(p1) != p1.EuclideanDistanceTo(p0)"
              << std::endl;
    return EXIT_FAILURE;
    }

  if( p1.EuclideanDistanceTo( p1 ) != 0. )
    {
    std::cerr << "p1.EuclideanDistanceTo(p1) != 0."
              << std::endl;
    return EXIT_FAILURE;
    }

  PointType::RealType dist2 = p0.SquaredEuclideanDistanceTo(p1);
  std::cout << "Dist2: " << dist2 << std::endl;

  if( vnl_math_abs( dist2 - dist * dist ) < vnl_math::eps )
    {
    std::cerr << "dist2 != dist * dist" << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
