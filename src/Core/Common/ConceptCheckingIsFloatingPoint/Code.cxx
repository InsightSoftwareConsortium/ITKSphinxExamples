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

#include "itkImage.h"
#include "itkConceptChecking.h"

template< typename TImage >
void IsPixelTypeFloatingPoint(const TImage* const)
{
  itkConceptMacro( nameOfCheck, ( itk::Concept::IsFloatingPoint< typename TImage::PixelType > ) );
}

int main( int, char* [] )
{
  constexpr unsigned int Dimension = 2;
  using FloatImageType = itk::Image< float, Dimension >;
  FloatImageType::Pointer f = FloatImageType::New();
  IsPixelTypeFloatingPoint( f.GetPointer() );

  using DoubleImageType = itk::Image< double, Dimension >;
  DoubleImageType::Pointer d = DoubleImageType::New();
  IsPixelTypeFloatingPoint( d.GetPointer() );

  return EXIT_SUCCESS;
}
