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
#include "itkBinaryStatisticsOpeningImageFilter.h"
#include "itkImageFileWriter.h"

using ImageType = itk::Image<unsigned char, 2>;
void
CreateImage(ImageType::Pointer image1, ImageType::Pointer image2);

int
main()
{
  ImageType::Pointer binaryImage = ImageType::New();
  ImageType::Pointer featureImage = ImageType::New();

  CreateImage(binaryImage, featureImage);

  using BinaryOpeningType = itk::BinaryStatisticsOpeningImageFilter<ImageType, ImageType>;
  BinaryOpeningType::Pointer opening = BinaryOpeningType::New();
  opening->SetInput(binaryImage);
  opening->SetFeatureImage(featureImage);
  opening->SetBackgroundValue(0);
  opening->SetForegroundValue(255);
  opening->SetLambda(150);
  opening->SetAttribute(BinaryOpeningType::LabelObjectType::MEAN);
  opening->Update();

  itk::WriteImage(featureImage, "input.mhd");
  itk::WriteImage(opening->GetOutput(), "output.mhd");

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image1, ImageType::Pointer image2)
{
  // Create an image with 2 connected components
  ImageType::RegionType region;
  ImageType::IndexType  start;
  start[0] = 0;
  start[1] = 0;

  ImageType::SizeType size;
  size[0] = 200;
  size[1] = 200;

  region.SetSize(size);
  region.SetIndex(start);

  image1->SetRegions(region);
  image1->Allocate();
  image1->FillBuffer(0);

  image2->SetRegions(region);
  image2->Allocate();
  image2->FillBuffer(0);

  // Make a square
  for (unsigned int r = 20; r < 80; r++)
  {
    for (unsigned int c = 30; c < 100; c++)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image1->SetPixel(pixelIndex, 255);
      image2->SetPixel(pixelIndex, 100);
    }
  }

  // Make another square
  for (unsigned int r = 100; r < 130; r++)
  {
    for (unsigned int c = 115; c < 160; c++)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image1->SetPixel(pixelIndex, 255);
      image2->SetPixel(pixelIndex, 200);
    }
  }
}
