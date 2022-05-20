/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#include "itkCovariantVector.h"
#include "itkGradientImageFilter.h"
#include "itkImageRegionIterator.h"

int
main(int argc, char * argv[])
{
  // Setup types
  using VectorType = itk::CovariantVector<float, 2>;
  using VectorImageType = itk::Image<VectorType, 2>;
  auto image = VectorImageType::New();

  itk::Size<2> size;
  size[0] = 5;
  size[1] = 5;

  itk::Index<2> index;
  index[0] = 0;
  index[1] = 0;

  VectorImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(index);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<VectorImageType> iterator(image, region);

  while (!iterator.IsAtEnd())
  {
  }

  // Create and setup a gradient filter
  using GradientFilterType = itk::GradientImageFilter<VectorImageType, VectorType>;
  auto gradientFilter = GradientFilterType::New();
  gradientFilter->SetInput(image);
  gradientFilter->Update();

  return EXIT_SUCCESS;
}
