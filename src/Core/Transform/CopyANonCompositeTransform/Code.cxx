#include "itkEuler3DTransform.h"

int main( int, char* [] )
{
  typedef itk::Euler3DTransform< float > TransformType;

  TransformType::Pointer transform = TransformType::New();
  TransformType::ParametersType parameters( 6 );
  parameters[0] = 0.1;
  parameters[1] = 0.2;
  parameters[2] = 0.3;
  parameters[3] = 4.0;
  parameters[4] = 5.0;
  parameters[5] = 6.0;
  transform->SetParameters( parameters );
#if defined(ITK_FIXED_PARAMETERS_ARE_DOUBLE) // After 4.8.1
   TransformType::FixedParametersType fixedParameters(3);
#else                                         //Pre 4.8.1
  TransformType::ParametersType fixedParameters(3);
#endif
  fixedParameters[0] = -3.5;
  fixedParameters[1] = -4.5;
  fixedParameters[2] = -5.5;
  transform->SetFixedParameters( fixedParameters );
  std::cout << "Original transform: " << transform << std::endl;

  TransformType::Pointer transformCopy = transform->Clone();
  std::cout << "Transform copy: " << transformCopy << std::endl;

  return EXIT_SUCCESS;
}
