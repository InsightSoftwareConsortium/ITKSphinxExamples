#include "itkImage.h"
#include "itkRGBPixel.h"

int main(int, char *[])
{
  const unsigned int Dimension = 2;
  typedef itk::RGBPixel< unsigned char > RGBPixelType;

  typedef itk::Image< RGBPixelType, Dimension > RGBImageType;
  RGBImageType::Pointer image = RGBImageType::New();

  return EXIT_SUCCESS;
}
