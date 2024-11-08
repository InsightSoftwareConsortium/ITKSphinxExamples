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
#include "itkNoiseImageFilter.h"
#include "itkImageFileWriter.h"

using ImageType = itk::Image<float, 2>;

void
CreateImage(ImageType::Pointer image);

int
main(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  auto image = ImageType::New();
  CreateImage(image);

  using NoiseImageFilterType = itk::NoiseImageFilter<ImageType, ImageType>;
  auto noiseImageFilter = NoiseImageFilterType::New();
  noiseImageFilter->SetInput(image);
  noiseImageFilter->SetRadius(1);
  noiseImageFilter->Update();

  itk::WriteImage(noiseImageFilter->GetOutput(), "output.mhd");

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  // Create an image that is mostly constant but has some different kinds of objects.
  ImageType::IndexType start{};

  ImageType::SizeType size;
  size.Fill(100);

  ImageType::RegionType region(start, size);

  // Create a black image
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  // Create a white square
  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] > 50 && imageIterator.GetIndex()[0] < 70 && imageIterator.GetIndex()[1] > 50 &&
        imageIterator.GetIndex()[1] < 70)
    {
      imageIterator.Set(255);
    }
    ++imageIterator;
  }

  // Create a rogue white pixel
  ImageType::IndexType pixel;
  pixel.Fill(20);
  image->SetPixel(pixel, 255);

  itk::WriteImage(image, "input.mhd");
}
