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
#include "itkSquaredDifferenceImageFilter.h"
#include "itkImageRegionIterator.h"

using UnsignedCharImageType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;

static void
CreateImage1(UnsignedCharImageType::Pointer image);
static void
CreateImage2(UnsignedCharImageType::Pointer image);

int
main(int, char *[])
{
  UnsignedCharImageType::Pointer image1 = UnsignedCharImageType::New();
  CreateImage1(image1);

  UnsignedCharImageType::Pointer image2 = UnsignedCharImageType::New();
  CreateImage2(image2);

  using SquaredDifferenceImageFilterType =
    itk::SquaredDifferenceImageFilter<UnsignedCharImageType, UnsignedCharImageType, FloatImageType>;

  SquaredDifferenceImageFilterType::Pointer squaredDifferenceFilter = SquaredDifferenceImageFilterType::New();
  squaredDifferenceFilter->SetInput1(image1);
  squaredDifferenceFilter->SetInput2(image2);
  squaredDifferenceFilter->Update();

  return EXIT_SUCCESS;
}

void
CreateImage1(UnsignedCharImageType::Pointer image)
{
  UnsignedCharImageType::IndexType start;
  start.Fill(0);

  UnsignedCharImageType::SizeType size;
  size.Fill(10);

  UnsignedCharImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<UnsignedCharImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    imageIterator.Set(255);

    ++imageIterator;
  }
}


void
CreateImage2(UnsignedCharImageType::Pointer image)
{
  // Create an image with 2 connected components
  UnsignedCharImageType::IndexType start;
  start.Fill(0);

  UnsignedCharImageType::SizeType size;
  size.Fill(10);

  UnsignedCharImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<UnsignedCharImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    imageIterator.Set(100);

    ++imageIterator;
  }
}
