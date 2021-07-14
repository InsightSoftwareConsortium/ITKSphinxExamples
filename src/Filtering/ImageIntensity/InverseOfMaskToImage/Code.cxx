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
#include "itkMaskNegatedImageFilter.h"

using ImageType = itk::Image<unsigned char, 2>;

static void
CreateHalfMask(ImageType::Pointer image, ImageType::Pointer mask);
static void
CreateImage(ImageType::Pointer image);

int
main(int, char *[])
{
  ImageType::Pointer image = ImageType::New();
  CreateImage(image);

  ImageType::Pointer mask = ImageType::New();
  CreateHalfMask(image, mask);

  using MaskNegatedImageFilterType = itk::MaskNegatedImageFilter<ImageType, ImageType>;
  MaskNegatedImageFilterType::Pointer maskNegatedImageFilter = MaskNegatedImageFilterType::New();
  maskNegatedImageFilter->SetInput(image);
  maskNegatedImageFilter->SetMaskImage(mask);
  maskNegatedImageFilter->Update();

  itk::WriteImage(maskNegatedImageFilter->GetOutput(), "output.png");

  return EXIT_SUCCESS;
}


void
CreateHalfMask(ImageType::Pointer image, ImageType::Pointer mask)
{
  ImageType::RegionType region = image->GetLargestPossibleRegion();

  mask->SetRegions(region);
  mask->Allocate();

  ImageType::SizeType regionSize = region.GetSize();

  itk::ImageRegionIterator<ImageType> imageIterator(mask, region);

  // Make the left half of the mask white and the right half black
  while (!imageIterator.IsAtEnd())
  {
    if (static_cast<unsigned int>(imageIterator.GetIndex()[0]) > regionSize[0] / 2)
    {
      imageIterator.Set(0);
    }
    else
    {
      imageIterator.Set(1);
    }

    ++imageIterator;
  }
}

void
CreateImage(ImageType::Pointer image)
{
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(100);

  ImageType::RegionType region(start, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(122);
}
