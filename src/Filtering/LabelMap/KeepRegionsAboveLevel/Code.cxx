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
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include "itkBinaryImageToLabelMapFilter.h"
#include "itkLabelShapeKeepNObjectsImageFilter.h"
#include "itkLabelMapToLabelImageFilter.h"
#include "itkScalarToRGBColormapImageFilter.h"

using ImageType = itk::Image<unsigned char, 2>;
using LabelImageType = itk::Image<unsigned char, 2>;
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

  using LabelMapToLabelImageFilterType =
    itk::LabelMapToLabelImageFilter<BinaryImageToLabelMapFilterType::OutputImageType, LabelImageType>;
  auto labelMapToLabelImageFilter = LabelMapToLabelImageFilterType::New();
  labelMapToLabelImageFilter->SetInput(binaryImageToLabelMapFilter->GetOutput());
  labelMapToLabelImageFilter->Update();

  using LabelShapeKeepNObjectsImageFilterType = itk::LabelShapeKeepNObjectsImageFilter<LabelImageType>;
  LabelShapeKeepNObjectsImageFilterType::Pointer labelShapeKeepNObjectsImageFilter =
    LabelShapeKeepNObjectsImageFilterType::New();
  labelShapeKeepNObjectsImageFilter->SetInput(labelMapToLabelImageFilter->GetOutput());
  labelShapeKeepNObjectsImageFilter->SetBackgroundValue(0);
  labelShapeKeepNObjectsImageFilter->SetNumberOfObjects(2);
  // KeepNObjects->ReverseOrderingOn();
  // labelShapeKeepNObjectsImageFilter->SetAttribute( LabelObjectType::PERIMETER );
  labelShapeKeepNObjectsImageFilter->SetAttribute(LabelShapeKeepNObjectsImageFilterType::LabelObjectType::PERIMETER);
  labelShapeKeepNObjectsImageFilter->Update();

  using RGBPixelType = itk::RGBPixel<unsigned char>;
  using RGBImageType = itk::Image<RGBPixelType, 2>;

  // Color each label/object a different color
  using RGBFilterType = itk::ScalarToRGBColormapImageFilter<LabelImageType, RGBImageType>;
  auto colormapImageFilter = RGBFilterType::New();
  colormapImageFilter->SetInput(labelShapeKeepNObjectsImageFilter->GetOutput());
  colormapImageFilter->SetColormap(itk::ScalarToRGBColormapImageFilterEnums::RGBColormapFilter::Jet);
  colormapImageFilter->Update();

  itk::WriteImage(colormapImageFilter->GetOutput(), "output.png");

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  // Create a black image with three white squares
  ImageType::IndexType start{};

  ImageType::SizeType size;
  size.Fill(200);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);
  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image, image->GetLargestPossibleRegion());

  // Make a square
  while (!imageIterator.IsAtEnd())
  {
    if (((imageIterator.GetIndex()[0] > 5 && imageIterator.GetIndex()[0] < 20) &&
         (imageIterator.GetIndex()[1] > 5 && imageIterator.GetIndex()[1] < 20)) ||
        ((imageIterator.GetIndex()[0] > 50 && imageIterator.GetIndex()[0] < 60) &&
         (imageIterator.GetIndex()[1] > 50 && imageIterator.GetIndex()[1] < 60)) ||
        ((imageIterator.GetIndex()[0] > 100 && imageIterator.GetIndex()[0] < 130) &&
         (imageIterator.GetIndex()[1] > 100 && imageIterator.GetIndex()[1] < 130)))
    {
      imageIterator.Set(255);
    }
    else
    {
      imageIterator.Set(0);
    }

    ++imageIterator;
  }

  itk::WriteImage(image, "input.png");
}
