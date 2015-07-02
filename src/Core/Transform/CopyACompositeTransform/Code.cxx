#include "itkEuler3DTransform.h"
#include "itkScaleTransform.h"
#include "itkCompositeTransform.h"
#include "itkCompositeTransformIOHelper.h"

int main( int , char* [] )
{
  typedef float ScalarType;
  const unsigned int Dimension = 3;

  typedef itk::Euler3DTransform< ScalarType > EulerTransformType;
  EulerTransformType::Pointer eulerTransform = EulerTransformType::New();
  EulerTransformType::ParametersType eulerParameters( 6 );
  eulerParameters[0] = 0.1;
  eulerParameters[1] = 0.2;
  eulerParameters[2] = 0.3;
  eulerParameters[3] = 4.0;
  eulerParameters[4] = 5.0;
  eulerParameters[5] = 6.0;
  eulerTransform->SetParameters( eulerParameters );
  EulerTransformType::ParametersType eulerFixedParameters( Dimension );
  eulerFixedParameters[0] = -3.5;
  eulerFixedParameters[1] = -4.5;
  eulerFixedParameters[2] = -5.5;
  eulerTransform->SetFixedParameters( eulerFixedParameters );

  typedef itk::ScaleTransform< ScalarType, Dimension > ScaleTransformType;
  ScaleTransformType::Pointer scaleTransform = ScaleTransformType::New();
  ScaleTransformType::ParametersType scaleParameters( Dimension );
  scaleParameters[0] = 0.6;
  scaleParameters[1] = 0.7;
  scaleParameters[2] = 0.8;
  scaleTransform->SetParameters( scaleParameters );

  typedef itk::CompositeTransform< ScalarType, Dimension > CompositeTransformType;
  CompositeTransformType::Pointer compositeTransform = CompositeTransformType::New();
  compositeTransform->AddTransform( eulerTransform );
  compositeTransform->AddTransform( scaleTransform );
  std::cout << "Original transform: " << compositeTransform << std::endl;


  CompositeTransformType::Pointer transformCopy = compositeTransform->Clone();
  std::cout << "Transform copy: " << transformCopy << std::endl;

  return EXIT_SUCCESS;
}
