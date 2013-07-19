#include "itkBinaryBallStructuringElement.h"

int main(int, char *[])
{
  const unsigned int Dimension = 3;
  typedef float PixelType;

  typedef itk::BinaryBallStructuringElement< PixelType, Dimension >
    StructuringElementType;
  StructuringElementType structuringElement;
  structuringElement.SetRadius(5);
  structuringElement.CreateStructuringElement();

  return EXIT_SUCCESS;
}
