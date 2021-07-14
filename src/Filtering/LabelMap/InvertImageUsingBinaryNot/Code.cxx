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
#if ITK_VERSION_MAJOR >= 4
#  include "itkBinaryNotImageFilter.h"
#endif
#include "itkImageRegionIterator.h"
#include "itkImageFileWriter.h"

using ImageType = itk::Image<unsigned char, 2>;
static void
CreateImage(ImageType::Pointer image);

int
main(int, char *[])
{
#if ITK_VERSION_MAJOR >= 4
  ImageType::Pointer image = ImageType::New();
  CreateImage(image);

  itk::WriteImage(image, "input.png");

  using BinaryNotImageFilterType = itk::BinaryNotImageFilter<ImageType>;

  BinaryNotImageFilterType::Pointer binaryNotFilter = BinaryNotImageFilterType::New();
  binaryNotFilter->SetInput(image);
  binaryNotFilter->Update();

  itk::WriteImage(binaryNotFilter->GetOutput(), "output.png");
#endif

  return EXIT_SUCCESS;
}
void
CreateImage(ImageType::Pointer image)
{
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(100);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] > 50)
    {
      imageIterator.Set(255);
    }
    else
    {
      imageIterator.Set(0);
    }

    ++imageIterator;
  }
}
