#include "itkImage.h"
#include "itkConceptChecking.h"

template< class TImage, class TValue >
void CheckIfPixelTypeIsTheSameAs( const TImage* const image )
{
  itkConceptMacro( nameOfCheck, ( itk::Concept::SameType< typename TImage::PixelType, TValue > ) );
}
int main( int argc, char* argv[] )
{
  const unsigned int Dimension = 2;
  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;
  ImageType::Pointer image = ImageType::New();

  CheckIfPixelTypeIsTheSameAs< ImageType, unsigned char >( image.GetPointer() );

  typedef itk::Image< PixelType, Dimension > ImageType2;

  CheckIfPixelTypeIsTheSameAs< ImageType, ImageType2::PixelType >( image.GetPointer() );

  return EXIT_SUCCESS;
}
