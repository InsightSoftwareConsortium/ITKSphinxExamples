#include "itkImage.h"
#include "itkConceptChecking.h"

template< typename TImage >
void IsPixelTypeFloatingPoint(const TImage* const)
{
  itkConceptMacro( nameOfCheck, ( itk::Concept::IsFloatingPoint< typename TImage::PixelType > ) );
}

int main( int, char* [] )
{
  const unsigned int Dimension = 2;
  typedef itk::Image< float, Dimension >  FloatImageType;
  FloatImageType::Pointer f = FloatImageType::New();
  IsPixelTypeFloatingPoint( f.GetPointer() );

  typedef itk::Image< double, Dimension > DoubleImageType;
  DoubleImageType::Pointer d = DoubleImageType::New();
  IsPixelTypeFloatingPoint( d.GetPointer() );

  return EXIT_SUCCESS;
}
