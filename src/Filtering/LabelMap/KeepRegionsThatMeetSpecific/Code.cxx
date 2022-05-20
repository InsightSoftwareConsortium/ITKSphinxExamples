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
#include "itkImageRegionIterator.h"
#include "itkBinaryImageToShapeLabelMapFilter.h"
#include "itkShapeOpeningLabelMapFilter.h"
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

  // Create a ShapeLabelMap from the image
  using BinaryImageToShapeLabelMapFilterType = itk::BinaryImageToShapeLabelMapFilter<ImageType>;
  BinaryImageToShapeLabelMapFilterType::Pointer binaryImageToShapeLabelMapFilter =
    BinaryImageToShapeLabelMapFilterType::New();
  binaryImageToShapeLabelMapFilter->SetInput(image);
  binaryImageToShapeLabelMapFilter->Update();

  // Remove label objects that have PERIMETER greater than 50
  using ShapeOpeningLabelMapFilterType =
    itk::ShapeOpeningLabelMapFilter<BinaryImageToShapeLabelMapFilterType::OutputImageType>;
  auto shapeOpeningLabelMapFilter = ShapeOpeningLabelMapFilterType::New();
  shapeOpeningLabelMapFilter->SetInput(binaryImageToShapeLabelMapFilter->GetOutput());
  shapeOpeningLabelMapFilter->SetLambda(50);
  shapeOpeningLabelMapFilter->ReverseOrderingOn();
  shapeOpeningLabelMapFilter->SetAttribute(ShapeOpeningLabelMapFilterType::LabelObjectType::PERIMETER);
  shapeOpeningLabelMapFilter->Update();

  // Create a label image
  using LabelMapToLabelImageFilterType =
    itk::LabelMapToLabelImageFilter<BinaryImageToShapeLabelMapFilterType::OutputImageType, LabelImageType>;
  auto labelMapToLabelImageFilter = LabelMapToLabelImageFilterType::New();
  labelMapToLabelImageFilter->SetInput(shapeOpeningLabelMapFilter->GetOutput());
  labelMapToLabelImageFilter->Update();

  using RGBPixelType = itk::RGBPixel<unsigned char>;
  using RGBImageType = itk::Image<RGBPixelType, 2>;

  // Color each label/object a different color
  using RGBFilterType = itk::ScalarToRGBColormapImageFilter<LabelImageType, RGBImageType>;
  auto colormapImageFilter = RGBFilterType::New();
  colormapImageFilter->SetInput(labelMapToLabelImageFilter->GetOutput());
  colormapImageFilter->SetColormap(itk::ScalarToRGBColormapImageFilterEnums::RGBColormapFilter::Jet);
  colormapImageFilter->Update();

  itk::WriteImage(colormapImageFilter->GetOutput(), "output.png");

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  // Create a black image with three white squares
  ImageType::IndexType start;
  start.Fill(0);

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
    if (((imageIterator.GetIndex()[0] > 5 && imageIterator.GetIndex()[0] < 10) &&
         (imageIterator.GetIndex()[1] > 5 && imageIterator.GetIndex()[1] < 10)) ||
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

  using WriterType = itk::ImageFileWriter<ImageType>;
  auto writer = WriterType::New();
  writer->SetFileName("input.png");
  writer->SetInput(image);
  writer->Update();
}
