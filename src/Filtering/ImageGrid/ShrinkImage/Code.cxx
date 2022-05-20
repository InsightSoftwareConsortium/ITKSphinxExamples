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
#include "itkRescaleIntensityImageFilter.h"
#include "itkShrinkImageFilter.h"

using ImageType = itk::Image<unsigned char, 2>;

static void
CreateImage(ImageType::Pointer image);

int
main(int, char *[])
{
  auto image = ImageType::New();
  CreateImage(image);

  std::cout << "Original size: " << image->GetLargestPossibleRegion().GetSize() << std::endl;

  using ShrinkImageFilterType = itk::ShrinkImageFilter<ImageType, ImageType>;

  auto shrinkFilter = ShrinkImageFilterType::New();
  shrinkFilter->SetInput(image);
  shrinkFilter->SetShrinkFactor(0, 2); // shrink the first dimension by a factor of 2 (i.e. 100 gets changed to 50)
  shrinkFilter->SetShrinkFactor(1, 3); // shrink the second dimension by a factor of 3 (i.e. 100 gets changed to 33)
  shrinkFilter->Update();

  std::cout << "New size: " << shrinkFilter->GetOutput()->GetLargestPossibleRegion().GetSize() << std::endl;


  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  // Create an image with 2 connected components
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(100);

  ImageType::RegionType region(start, size);
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  // Make a white square
  for (unsigned int r = 20; r < 80; r++)
  {
    for (unsigned int c = 20; c < 30; c++)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 255);
    }
  }
}
