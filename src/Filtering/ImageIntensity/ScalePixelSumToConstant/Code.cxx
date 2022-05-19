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
#include "itkImageRegionConstIterator.h"
#include "itkNormalizeToConstantImageFilter.h"

using ImageType = itk::Image<float, 2>;

static void
CreateImage(ImageType::Pointer image);

int
main(int, char *[])
{
  // Create an image
  auto image = ImageType::New();
  CreateImage(image);

  using NormalizeToConstantImageFilterType = itk::NormalizeToConstantImageFilter<ImageType, ImageType>;
  NormalizeToConstantImageFilterType::Pointer normalizeToConstantImageFilter =
    NormalizeToConstantImageFilterType::New();
  normalizeToConstantImageFilter->SetInput(image);
  normalizeToConstantImageFilter->SetConstant(1);
  normalizeToConstantImageFilter->Update();

  itk::ImageRegionConstIterator<ImageType> imageIterator(
    normalizeToConstantImageFilter->GetOutput(),
    normalizeToConstantImageFilter->GetOutput()->GetLargestPossibleRegion());

  // The output pixels should all be 1/9 (=0.11111)
  while (!imageIterator.IsAtEnd())
  {
    std::cout << imageIterator.Get() << std::endl;
    ++imageIterator;
  }

  return EXIT_SUCCESS;
}

static void
CreateImage(ImageType::Pointer image)
{
  // Create an image full of 1's

  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(3);

  ImageType::RegionType region(start, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(1);
}
