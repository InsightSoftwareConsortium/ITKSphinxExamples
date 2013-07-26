#include "itkImage.h"

int main(int, char*[])
{
  const unsigned int Dimension = 2;
  typedef unsigned char PixelType;

  typedef itk::Image< PixelType, Dimension > ImageType;
  ImageType::Pointer image = ImageType::New();

  std::cout << "image is type: " << image->GetNameOfClass() << std::endl;

  return EXIT_SUCCESS;
}
