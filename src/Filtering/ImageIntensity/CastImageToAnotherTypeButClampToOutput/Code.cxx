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
#include "itkClampImageFilter.h"

using FloatImageType = itk::Image<float, 2>;
using UnsignedCharImageType = itk::Image<unsigned char, 2>;

static void
CreateImage(FloatImageType * const image);

int
main(int argc, char * argv[])
{
  FloatImageType::Pointer image;

  // No input image argument provided
  if (argc < 2)
  {
    image = FloatImageType::New();
    CreateImage(image);
  }
  else // Input image argument provided
  {
    image = itk::ReadImage<FloatImageType>(argv[1]);
  }

  using ClampFilterType = itk::ClampImageFilter<FloatImageType, UnsignedCharImageType>;
  auto clampFilter = ClampFilterType::New();
  clampFilter->SetInput(image);
  clampFilter->Update();

  return EXIT_SUCCESS;
}

void
CreateImage(FloatImageType * const image)
{
  // Create an image with 2 connected components
  FloatImageType::IndexType corner = { { 0, 0 } };

  FloatImageType::SizeType size;
  unsigned int             NumRows = 200;
  unsigned int             NumCols = 300;
  size[0] = NumRows;
  size[1] = NumCols;

  FloatImageType::RegionType region(corner, size);

  image->SetRegions(region);
  image->Allocate();

  // Make a square
  for (unsigned int r = 40; r < 100; r++)
  {
    for (unsigned int c = 40; c < 100; c++)
    {
      FloatImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 15);
    }
  }
}
