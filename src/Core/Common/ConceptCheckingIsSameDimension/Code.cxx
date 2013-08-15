#include "itkImage.h"
#include "itkConceptChecking.h"

template< class TImage, unsigned int VDimension >
void CheckIfDimensionIsTheSame( const TImage* const image )
{
  itkConceptMacro( nameOfCheck, ( itk::Concept::SameDimension< TImage::ImageDimension, VDimension > ) );
}
int main( int argc, char* argv[] )
{
  const unsigned int Dimension = 2;
  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;
  ImageType::Pointer image = ImageType::New();

  CheckIfDimensionIsTheSame< ImageType, 2 >( image.GetPointer() );

  typedef itk::Image< PixelType, Dimension > ImageType2;

  CheckIfDimensionIsTheSame< ImageType, ImageType2::ImageDimension >( image.GetPointer() );

  return EXIT_SUCCESS;
}
