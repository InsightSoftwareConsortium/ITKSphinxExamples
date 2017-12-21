/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

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
  TransformType::FixedParametersType fixedParameters( 3 );
  fixedParameters[0] = -3.5;
  fixedParameters[1] = -4.5;
  fixedParameters[2] = -5.5;
  transform->SetFixedParameters( fixedParameters );
  std::cout << "Original transform: " << transform << std::endl;

  TransformType::Pointer transformCopy = transform->Clone();
  std::cout << "Transform copy: " << transformCopy << std::endl;

  return EXIT_SUCCESS;
}
