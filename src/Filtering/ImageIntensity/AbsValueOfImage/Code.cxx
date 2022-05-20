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
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkAbsImageFilter.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

using UnsignedCharImageType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;

static void
CreateImage(FloatImageType::Pointer image);

int
main(int, char *[])
{
  auto image = FloatImageType::New();
  CreateImage(image);

  // Take the absolute value of the image
  using AbsImageFilterType = itk::AbsImageFilter<FloatImageType, FloatImageType>;

  auto absFilter = AbsImageFilterType::New();
  absFilter->SetInput(image);

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage<FloatImageType>(image);
  viewer.AddImage<FloatImageType>(absFilter->GetOutput());
  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}

void
CreateImage(FloatImageType::Pointer image)
{
  // Create an image with negative values
  FloatImageType::RegionType region;
  FloatImageType::IndexType  start;
  start[0] = 0;
  start[1] = 0;

  FloatImageType::SizeType size;
  size[0] = 200;
  size[1] = 300;

  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<FloatImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    imageIterator.Set(imageIterator.GetIndex()[0] - imageIterator.GetIndex()[1]);
    ++imageIterator;
  }
}
