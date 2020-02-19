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
#include "itkImageFileReader.h"
#include "itkCustomColormapFunction.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkRGBPixel.h"
#include "itkMersenneTwisterRandomVariateGenerator.h"

#include "itkRelabelComponentImageFilter.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

using RGBPixelType = itk::RGBPixel<unsigned char>;
using RGBImageType = itk::Image<RGBPixelType, 2>;
using ImageType = itk::Image<unsigned char, 2>;
using ColormapType = itk::Function::CustomColormapFunction<ImageType::PixelType, RGBImageType::PixelType>;

static void
CreateImage(ImageType::Pointer image);
static void
CreateRandomColormap(unsigned int size, ColormapType::Pointer colormap);

int
main(int, char *[])
{
  ImageType::Pointer image = ImageType::New();

  CreateImage(image);

  using FilterType = itk::RelabelComponentImageFilter<ImageType, ImageType>;
  FilterType::Pointer relabelFilter = FilterType::New();
  relabelFilter->SetInput(image);

  using ColormapFilterType = itk::ScalarToRGBColormapImageFilter<ImageType, RGBImageType>;
  ColormapFilterType::Pointer colormapFilter1 = ColormapFilterType::New();

  ColormapType::Pointer largeColormap = ColormapType::New();
  CreateRandomColormap(255, largeColormap);

  colormapFilter1->SetInput(image);
  colormapFilter1->SetColormap(largeColormap);

  ColormapFilterType::Pointer colormapFilter2 = ColormapFilterType::New();
  colormapFilter2->SetInput(relabelFilter->GetOutput());
  colormapFilter2->SetColormap(largeColormap);

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddRGBImage(colormapFilter1->GetOutput(), true, "Original");

  viewer.AddRGBImage(colormapFilter2->GetOutput(), true, "Relabeled");

  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  // Create an image with 2 connected components
  ImageType::RegionType region;
  ImageType::IndexType  start;
  start[0] = 0;
  start[1] = 0;

  ImageType::SizeType size;
  size[0] = 200;
  size[1] = 300;

  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] > 100 && imageIterator.GetIndex()[0] < 150 && imageIterator.GetIndex()[1] > 100 &&
        imageIterator.GetIndex()[1] < 150)
    {
      imageIterator.Set(200);
    }
    else if (imageIterator.GetIndex()[0] > 50 && imageIterator.GetIndex()[0] < 70 && imageIterator.GetIndex()[1] > 50 &&
             imageIterator.GetIndex()[1] < 70)
    {
      imageIterator.Set(100);
    }
    else
    {
      imageIterator.Set(0);
    }

    ++imageIterator;
  }
}

void
CreateRandomColormap(unsigned int size, ColormapType::Pointer colormap)
{
  ColormapType::ChannelType                                       redChannel;
  ColormapType::ChannelType                                       greenChannel;
  ColormapType::ChannelType                                       blueChannel;
  itk::Statistics::MersenneTwisterRandomVariateGenerator::Pointer random =
    itk::Statistics::MersenneTwisterRandomVariateGenerator::New();

  random->SetSeed(8775070);
  for (unsigned int i = 0; i < size; ++i)
  {
    redChannel.push_back(static_cast<ColormapType::RealType>(random->GetUniformVariate(.3, 1.0)));
    greenChannel.push_back(static_cast<ColormapType::RealType>(random->GetUniformVariate(.3, 1.0)));
    blueChannel.push_back(static_cast<ColormapType::RealType>(random->GetUniformVariate(.3, 1.0)));
  }
  colormap->SetRedChannel(redChannel);
  colormap->SetGreenChannel(greenChannel);
  colormap->SetBlueChannel(blueChannel);
}
