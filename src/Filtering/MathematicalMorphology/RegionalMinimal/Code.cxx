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
#include "itkRegionalMinimaImageFilter.h"

using ImageType = itk::Image<unsigned char, 2>;

static void
CreateImage(ImageType::Pointer image);

int
main()
{
  auto image = ImageType::New();
  CreateImage(image);

  using RegionalMinimaImageFilterType = itk::RegionalMinimaImageFilter<ImageType, ImageType>;
  auto regionalMinimaImageFilter = RegionalMinimaImageFilterType::New();
  regionalMinimaImageFilter->SetInput(image);
  regionalMinimaImageFilter->Update();

  itk::WriteImage(image, "input.png");

  itk::WriteImage(regionalMinimaImageFilter->GetOutput(), "output.png");

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size[0] = 200;
  size[1] = 300;

  ImageType::RegionType region(start, size);

  image->SetRegions(region);
  image->Allocate();

  // Make two intensity blobs
  for (unsigned int r = 0; r < size[1]; r++)
  {
    for (unsigned int c = 0; c < size[0]; c++)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = c;
      pixelIndex[1] = r;

      double c1 = c - 100.0;
      double c2 = c - 200.0;

      double rr = r - 100.0;

      // purposely use 270,257 since it is > 255
      double v1 = 270.0 - std::sqrt(rr * rr + c1 * c1);
      double v2 = 257.0 - std::sqrt(rr * rr + c2 * c2);

      double maxv = v1;
      if (maxv < v2)
        maxv = v2;

      double val = maxv;

      // Clip
      if (val < 0.0)
        val = 0.0;
      if (val > 255.0)
        val = 255.0;

      image->SetPixel(pixelIndex, static_cast<unsigned char>(val));
    }
  }
}
