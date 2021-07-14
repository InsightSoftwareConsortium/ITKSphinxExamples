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
#include "itkBinaryImageToLabelMapFilter.h"
#include "itkImage.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include "itkLabelMapToLabelImageFilter.h"
#include "itkLabelOverlayImageFilter.h"
#include "itkRGBPixel.h"

using ImageType = itk::Image<unsigned char, 2>;
static void
CreateImage(ImageType::Pointer image);

int
main(int, char *[])
{
  ImageType::Pointer image = ImageType::New();
  CreateImage(image);

  using BinaryImageToLabelMapFilterType = itk::BinaryImageToLabelMapFilter<ImageType>;
  BinaryImageToLabelMapFilterType::Pointer binaryImageToLabelMapFilter = BinaryImageToLabelMapFilterType::New();
  binaryImageToLabelMapFilter->SetInput(image);
  binaryImageToLabelMapFilter->Update();

  using LabelMapToLabelImageFilterType =
    itk::LabelMapToLabelImageFilter<BinaryImageToLabelMapFilterType::OutputImageType, ImageType>;
  LabelMapToLabelImageFilterType::Pointer labelMapToLabelImageFilter = LabelMapToLabelImageFilterType::New();
  labelMapToLabelImageFilter->SetInput(binaryImageToLabelMapFilter->GetOutput());
  labelMapToLabelImageFilter->Update();

  using RGBPixelType = itk::RGBPixel<unsigned char>;
  using RGBImageType = itk::Image<RGBPixelType>;

  using LabelOverlayImageFilterType = itk::LabelOverlayImageFilter<ImageType, ImageType, RGBImageType>;
  LabelOverlayImageFilterType::Pointer labelOverlayImageFilter = LabelOverlayImageFilterType::New();
  labelOverlayImageFilter->SetInput(image);
  labelOverlayImageFilter->SetLabelImage(labelMapToLabelImageFilter->GetOutput());
  labelOverlayImageFilter->SetOpacity(.5);
  labelOverlayImageFilter->Update();

  itk::WriteImage(labelOverlayImageFilter->GetOutput(), "output.png");

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  // Create a black image with a white square
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(100);

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

  itk::WriteImage(image, "input.png");
}
