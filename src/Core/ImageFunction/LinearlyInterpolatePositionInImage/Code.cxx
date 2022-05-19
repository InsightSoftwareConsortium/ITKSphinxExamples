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
#include "itkContinuousIndex.h"
#include "itkLinearInterpolateImageFunction.h"

using ImageType = itk::Image<unsigned char, 1>;

static void
CreateImage(ImageType::Pointer image);

int
main()
{
  ImageType::Pointer image = ImageType::New();
  CreateImage(image);

  itk::ContinuousIndex<double, 1> pixel;
  pixel[0] = 1.3;

  itk::LinearInterpolateImageFunction<ImageType, double>::Pointer interpolator =
    itk::LinearInterpolateImageFunction<ImageType, double>::New();
  interpolator->SetInputImage(image);

  std::cout << "Value at 1.3: " << interpolator->EvaluateAtContinuousIndex(pixel) << std::endl;

  return EXIT_SUCCESS;
}


void
CreateImage(ImageType::Pointer image)
{
  // Create a 1D image
  ImageType::RegionType region;
  ImageType::IndexType  start;
  start[0] = 0;

  ImageType::SizeType size;
  size[0] = 10;

  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  for (unsigned int i = 0; i < 10; i++)
  {
    ImageType::IndexType pixelIndex;
    pixelIndex[0] = i;

    image->SetPixel(pixelIndex, i * 10);
  }
}
