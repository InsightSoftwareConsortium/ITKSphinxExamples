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
#include "itkImageAdaptor.h"
#include "itkImageRegionIterator.h"
#include "itkComposeImageFilter.h"

using VectorImageType = itk::Image<itk::CovariantVector<float, 3>, 2>;
using ScalarImageType = itk::Image<float, 2>;

static void
CreateImage(ScalarImageType::Pointer image);

int
main()
{
  ScalarImageType::Pointer image = ScalarImageType::New();
  CreateImage(image);

  using ComposeCovariantVectorImageFilterType = itk::ComposeImageFilter<ScalarImageType, VectorImageType>;
  ComposeCovariantVectorImageFilterType::Pointer composeFilter = ComposeCovariantVectorImageFilterType::New();

  composeFilter->SetInput1(image);
  composeFilter->SetInput2(image);
  composeFilter->SetInput3(image);
  composeFilter->Update();

  itk::Index<2> index;
  index.Fill(0);

  std::cout << image->GetPixel(index) << std::endl;

  std::cout << composeFilter->GetOutput()->GetPixel(index) << std::endl;

  return EXIT_SUCCESS;
}

void
CreateImage(ScalarImageType::Pointer image)
{
  ScalarImageType::IndexType start;
  start.Fill(0);

  ScalarImageType::SizeType size;
  size.Fill(2);

  ScalarImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ScalarImageType> imageIterator(image, image->GetLargestPossibleRegion());

  while (!imageIterator.IsAtEnd())
  {
    imageIterator.Set(1.2);

    ++imageIterator;
  }
}
