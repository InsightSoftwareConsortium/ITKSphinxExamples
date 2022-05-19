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
#include "itkMaskImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkMaskNeighborhoodOperatorImageFilter.h"
#include "itkSobelOperator.h"

namespace
{
using UnsignedCharImageType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;
} // namespace

static void
CreateImage(UnsignedCharImageType::Pointer image);
static void
CreateHalfMask(UnsignedCharImageType::Pointer image, UnsignedCharImageType::Pointer mask);

int
main(int, char *[])
{
  auto image = UnsignedCharImageType::New();
  CreateImage(image);

  auto mask = UnsignedCharImageType::New();
  CreateHalfMask(image, mask);

  using SobelOperatorType = itk::SobelOperator<float, 2>;
  SobelOperatorType sobelOperator;
  itk::Size<2>      radius;
  radius.Fill(1);                // a radius of 1x1 creates a 3x3 operator
  sobelOperator.SetDirection(0); // Create the operator for the X axis derivative
  sobelOperator.CreateToRadius(radius);

  // Visualize mask image
  using MaskNeighborhoodOperatorImageFilterType =
    itk::MaskNeighborhoodOperatorImageFilter<UnsignedCharImageType, UnsignedCharImageType, FloatImageType, float>;
  MaskNeighborhoodOperatorImageFilterType::Pointer maskNeighborhoodOperatorImageFilter =
    MaskNeighborhoodOperatorImageFilterType::New();
  maskNeighborhoodOperatorImageFilter->SetInput(image);
  maskNeighborhoodOperatorImageFilter->SetMaskImage(mask);
  maskNeighborhoodOperatorImageFilter->SetOperator(sobelOperator);
  maskNeighborhoodOperatorImageFilter->Update();

  using RescaleFilterType = itk::RescaleIntensityImageFilter<FloatImageType, UnsignedCharImageType>;
  auto rescaleFilter = RescaleFilterType::New();
  rescaleFilter->SetInput(maskNeighborhoodOperatorImageFilter->GetOutput());
  rescaleFilter->Update();

  itk::WriteImage(rescaleFilter->GetOutput(), "output.png");

  return EXIT_SUCCESS;
}


void
CreateHalfMask(UnsignedCharImageType::Pointer image, UnsignedCharImageType::Pointer mask)
{
  itk::ImageRegion<2> region = image->GetLargestPossibleRegion();

  mask->SetRegions(region);
  mask->Allocate();
  mask->FillBuffer(0);

  itk::Size<2> regionSize = region.GetSize();

  itk::ImageRegionIterator<UnsignedCharImageType> imageIterator(mask, region);

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

  using RescaleFilterType = itk::RescaleIntensityImageFilter<UnsignedCharImageType, UnsignedCharImageType>;
  auto rescaleFilter = RescaleFilterType::New();
  rescaleFilter->SetInput(mask);
  rescaleFilter->Update();

  itk::WriteImage(rescaleFilter->GetOutput(), "mask.png");
}


void
CreateImage(UnsignedCharImageType::Pointer image)
{
  itk::Index<2> start;
  start.Fill(0);

  itk::Size<2> size;
  size.Fill(100);

  itk::ImageRegion<2> region(start, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  // Make a square
  for (unsigned int r = 30; r < 70; r++)
  {
    for (unsigned int c = 30; c < 70; c++)
    {
      FloatImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 255);
    }
  }

  itk::WriteImage(image, "input.png");
}
