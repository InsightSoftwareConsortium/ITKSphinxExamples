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
#include "itkInvertIntensityImageFilter.h"
#include "itkBinaryContourImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif
using ImageType = itk::Image<unsigned char, 2>;

static void
CreateImage(ImageType::Pointer image);

int
main(int, char *[])
{
  ImageType::Pointer image = ImageType::New();
  CreateImage(image);

  using binaryContourImageFilterType = itk::BinaryContourImageFilter<ImageType, ImageType>;

  // Outer boundary
  binaryContourImageFilterType::Pointer binaryContourFilter = binaryContourImageFilterType::New();
  binaryContourFilter->SetInput(image);
  binaryContourFilter->SetForegroundValue(0);
  binaryContourFilter->SetBackgroundValue(255);
  binaryContourFilter->Update();

  // Invert the result
  using InvertIntensityImageFilterType = itk::InvertIntensityImageFilter<ImageType>;

  InvertIntensityImageFilterType::Pointer invertIntensityFilter = InvertIntensityImageFilterType::New();
  invertIntensityFilter->SetInput(binaryContourFilter->GetOutput());
  invertIntensityFilter->Update();

  ImageType::Pointer outerBoundary = ImageType::New();
  outerBoundary->Graft(invertIntensityFilter->GetOutput());

  // Inner boundary
  binaryContourFilter->SetForegroundValue(255);
  binaryContourFilter->SetBackgroundValue(0);
  binaryContourFilter->Update();

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(image.GetPointer());
  viewer.AddImage(outerBoundary.GetPointer());
  viewer.AddImage(binaryContourFilter->GetOutput());
  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(20);

  ImageType::RegionType region(start, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  // Make a square
  for (unsigned int r = 5; r < 10; r++)
  {
    for (unsigned int c = 5; c < 10; c++)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 255);
    }
  }
}
