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
#include "itkBinaryImageToLabelMapFilter.h"
#include "itkImage.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include "itkLabelMapToLabelImageFilter.h"
#include "itkLabelMapContourOverlayImageFilter.h"
#include "itkRGBPixel.h"

namespace
{
using ImageType = itk::Image<unsigned char, 2>;
}

static void
CreateImage(ImageType::Pointer image);

int
main()
{
  auto image = ImageType::New();
  CreateImage(image);

  using BinaryImageToLabelMapFilterType = itk::BinaryImageToLabelMapFilter<ImageType>;
  auto binaryImageToLabelMapFilter = BinaryImageToLabelMapFilterType::New();
  binaryImageToLabelMapFilter->SetInput(image);
  binaryImageToLabelMapFilter->Update();

  using RGBPixelType = itk::RGBPixel<unsigned char>;
  using RGBImageType = itk::Image<RGBPixelType>;

  using LabelMapContourOverlayImageFilterType =
    itk::LabelMapContourOverlayImageFilter<BinaryImageToLabelMapFilterType::OutputImageType, ImageType, RGBImageType>;
  LabelMapContourOverlayImageFilterType::Pointer labelMapContourOverlayImageFilter =
    LabelMapContourOverlayImageFilterType::New();
  labelMapContourOverlayImageFilter->SetInput(binaryImageToLabelMapFilter->GetOutput());
  labelMapContourOverlayImageFilter->SetFeatureImage(image);
  labelMapContourOverlayImageFilter->SetOpacity(.5);
  labelMapContourOverlayImageFilter->Update();

  itk::WriteImage(labelMapContourOverlayImageFilter->GetOutput(), "output.png");

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  // Create a black image with a white square
  ImageType::IndexType start{};

  auto size = ImageType::SizeType::Filled(100);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  itk::ImageRegionIterator<ImageType> imageIterator(image, image->GetLargestPossibleRegion());

  // Make two squares
  while (!imageIterator.IsAtEnd())
  {
    if ((imageIterator.GetIndex()[0] > 5 && imageIterator.GetIndex()[0] < 20) &&
        (imageIterator.GetIndex()[1] > 5 && imageIterator.GetIndex()[1] < 20))
    {
      imageIterator.Set(255);
    }

    if ((imageIterator.GetIndex()[0] > 50 && imageIterator.GetIndex()[0] < 70) &&
        (imageIterator.GetIndex()[1] > 50 && imageIterator.GetIndex()[1] < 70))
    {
      imageIterator.Set(255);
    }
    ++imageIterator;
  }

  itk::WriteImage(image, "image.png");
}
