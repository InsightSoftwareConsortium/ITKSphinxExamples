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
#include "itkImage.h"
#include "itkImageRegionExclusionConstIteratorWithIndex.h"

namespace
{
using ImageType = itk::Image<int, 2>;
}

static void CreateImage(ImageType::Pointer);

int
main()
{

  ImageType::SizeType exclusionRegionSize;
  exclusionRegionSize.Fill(2);

  ImageType::IndexType exclusionRegionIndex{};

  ImageType::RegionType exclusionRegion(exclusionRegionIndex, exclusionRegionSize);

  auto image = ImageType::New();
  CreateImage(image);

  itk::ImageRegionExclusionConstIteratorWithIndex<ImageType> imageIterator(image, image->GetLargestPossibleRegion());
  imageIterator.SetExclusionRegion(exclusionRegion);

  unsigned int numberVisited = 0;
  while (!imageIterator.IsAtEnd())
  {
    std::cout << imageIterator.Get() << std::endl;
    ++imageIterator;
    ++numberVisited;
  }

  std::cout << "Visited " << numberVisited << std::endl;

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  ImageType::SizeType regionSize;
  regionSize.Fill(3);

  ImageType::IndexType regionIndex{};

  ImageType::RegionType region(regionIndex, regionSize);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);
}
