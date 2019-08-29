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
#include "itkSimpleFilterWatcher.h"
#include "itkThresholdImageFilter.h"
#include "itkImageRegionIterator.h"

template <class TImage>
void
CreateImage(typename TImage::Pointer image)
{
  using ImageType = TImage;

  // Create an image with 2 connected components
  typename ImageType::RegionType region;
  typename ImageType::IndexType  start;
  start.Fill(0);

  typename ImageType::SizeType size;
  size.Fill(100);

  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    imageIterator.Set(255);
    ++imageIterator;
  }
}
int
main(int, char *[])
{
  constexpr unsigned int Dimension = 2;
  using PixelType = unsigned char;

  using ImageType = itk::Image<PixelType, Dimension>;

  ImageType::Pointer image = ImageType::New();
  CreateImage<ImageType>(image);

  using ThresholdImageFilterType = itk::ThresholdImageFilter<ImageType>;

  ThresholdImageFilterType::Pointer thresholdFilter = ThresholdImageFilterType::New();
  thresholdFilter->SetInput(image);
  thresholdFilter->ThresholdBelow(100);
  thresholdFilter->SetOutsideValue(0);

  itk::SimpleFilterWatcher watcher(thresholdFilter, "ThresholdFilter");

  thresholdFilter->Update();

  return EXIT_SUCCESS;
}
