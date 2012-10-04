#include "itkImage.h"

int main( int argc, char* argv[] )
{
  typedef itk::Image< unsigned short, 3 > ImageType;
  ImageType::Pointer image = ImageType::New();

  std::cout << "ITK Hello World!" << std::endl;
  std::cout << image << std::endl;

  return EXIT_SUCCESS;
}
