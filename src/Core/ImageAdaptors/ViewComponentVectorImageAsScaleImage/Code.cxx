/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include "itkVectorImage.h"
#include "itkImage.h"
#include "itkVectorImageToImageAdaptor.h"
#include "itkImageRegionIterator.h"

using ScalarImageType = itk::Image<float, 2>;
using VectorImageType = itk::VectorImage<float, 2>;

void
CreateImage(VectorImageType::Pointer image);

int
main()
{
  auto image = VectorImageType::New();
  CreateImage(image);

  using ImageAdaptorType = itk::VectorImageToImageAdaptor<float, 2>;
  auto adaptor = ImageAdaptorType::New();
  adaptor->SetExtractComponentIndex(0);
  adaptor->SetImage(image);

  itk::Index<2> index;
  index[0] = 0;
  index[1] = 0;

  std::cout << adaptor->GetPixel(index) << std::endl;

  return EXIT_SUCCESS;
}

void
CreateImage(VectorImageType::Pointer image)
{
  VectorImageType::IndexType start{};

  auto size = VectorImageType::SizeType::Filled(2);

  VectorImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->SetNumberOfComponentsPerPixel(2);
  image->Allocate();

  using VariableVectorType = itk::VariableLengthVector<double>;
  VariableVectorType variableLengthVector;
  variableLengthVector.SetSize(2);

  itk::ImageRegionIterator<VectorImageType> imageIterator(image, image->GetLargestPossibleRegion());
  variableLengthVector[0] = 1;
  variableLengthVector[1] = 2;

  while (!imageIterator.IsAtEnd())
  {
    imageIterator.Set(variableLengthVector);

    ++imageIterator;
  }
}
