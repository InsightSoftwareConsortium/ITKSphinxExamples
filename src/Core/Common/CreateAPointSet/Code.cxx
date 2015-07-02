#include "itkPoint.h"
#include "itkPointSet.h"

int main(int, char* [])
{
  typedef float PixelType;
  const unsigned int Dimension = 3;

  typedef itk::PointSet< PixelType, Dimension >   PointSetType;
  PointSetType::Pointer  PointSet = PointSetType::New();

  typedef PointSetType::PointsContainerPointer PointsContainerPointer;
  PointsContainerPointer  points = PointSet->GetPoints();

  // Create points
  typedef PointSetType::PointType PointType;
  PointType p0, p1, p2;

  p0[0]=  0.0; p0[1]= 0.0; p0[2]= 0.0;
  p1[0]=  0.1; p1[1]= 0.0; p1[2]= 0.0;
  p2[0]=  0.0; p2[1]= 0.1; p2[2]= 0.0;

  points->InsertElement(0, p0);
  points->InsertElement(1, p1);
  points->InsertElement(2, p2);

  return EXIT_SUCCESS;
}
