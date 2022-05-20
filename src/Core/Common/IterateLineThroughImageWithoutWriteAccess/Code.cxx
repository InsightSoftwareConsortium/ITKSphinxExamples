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
#include "itkImageRegionIterator.h"
#include "itkLineConstIterator.h"

using ImageType = itk::Image<unsigned char, 2>;

static void
CreateImage(ImageType::Pointer image);

int
main()
{
  auto image = ImageType::New();
  CreateImage(image);

  ImageType::RegionType region = image->GetLargestPossibleRegion();
  ImageType::IndexType  corner1 = region.GetIndex();
  ImageType::IndexType  corner2;
  corner2[0] = corner1[0] + region.GetSize()[0] - 1;
  corner2[1] = corner1[1] + region.GetSize()[1] - 1;

  itk::LineConstIterator<ImageType> it(image, corner1, corner2);
  it.GoToBegin();
  while (!it.IsAtEnd())
  {
    std::cout << (int)it.Get() << std::endl;
    ++it;
  }

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  ImageType::SizeType regionSize;
  regionSize.Fill(3);

  ImageType::IndexType regionIndex;
  regionIndex.Fill(0);

  ImageType::RegionType region;
  region.SetSize(regionSize);
  region.SetIndex(regionIndex);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image, image->GetLargestPossibleRegion());

  while (!imageIterator.IsAtEnd())
  {
    imageIterator.Set(255);
    ++imageIterator;
  }
}
