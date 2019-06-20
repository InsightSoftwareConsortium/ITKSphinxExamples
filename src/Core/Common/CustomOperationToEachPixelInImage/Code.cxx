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
#include "itkVectorImage.h"
#include "itkVector.h"
#include "itkVariableLengthVector.h"
#include "itkRigid2DTransform.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkMath.h"

template< class TInput, class TOutput>
class RotateVectors
{
public:
  RotateVectors() {};
  ~RotateVectors() {};
  bool operator!=( const RotateVectors & ) const
    {
    return false;
    }
  bool operator==( const RotateVectors & other ) const
    {
    return !(*this != other);
    }
  inline TOutput operator()( const TInput & A ) const
    {
      using VectorType = itk::Vector<float, 2>;
      VectorType v;
      v[0] = A[0];
      v[1] = A[1];
            
      using TransformType = itk::Rigid2DTransform< float >;

      TransformType::Pointer transform = TransformType::New();
      transform->SetAngle(itk::Math::pi/2.0);

      VectorType outputV = transform->TransformVector(v);
      TOutput transformedVector;
      transformedVector.SetSize(2);
      transformedVector[0] = outputV[0];
      transformedVector[1] = outputV[1];

      return transformedVector;
    }
};

int main(int, char *[])
{
  using ImageType = itk::VectorImage<float, 2>;

  ImageType::RegionType region;
  ImageType::IndexType start;
  start[0] = 0;
  start[1] = 0;

  ImageType::SizeType size;
  size[0] = 2;
  size[1] = 3;

  region.SetSize(size);
  region.SetIndex(start);

  ImageType::Pointer image = ImageType::New();
  image->SetRegions(region);
  image->SetVectorLength(2);
  image->Allocate();

  ImageType::IndexType pixelIndex;
  pixelIndex[0] = 1;
  pixelIndex[1] = 1;

  using VectorType = itk::VariableLengthVector<float>;
  VectorType v;
  v.SetSize(2);
  v[0] = 1;
  v[1] = 0;
  
  image->SetPixel(pixelIndex, v);
  
  using FilterType = itk::UnaryFunctorImageFilter<ImageType,ImageType,
                                  RotateVectors<
    ImageType::PixelType,
    ImageType::PixelType> >;

  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(image);
  filter->Update();

  ImageType::PixelType inputPixelValue = image->GetPixel(pixelIndex);
  ImageType::PixelType outputPixelValue = filter->GetOutput()->GetPixel(pixelIndex);

  std::cout << "pixel (1,1) was = " << inputPixelValue << std::endl;
  std::cout << "pixel (1,1) now = " << outputPixelValue << std::endl;

  return EXIT_SUCCESS;
}
