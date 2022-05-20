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
#include "itkImageFileReader.h"
#include "itkCropImageFilter.h"

#include "itksys/SystemTools.hxx"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

using PixelType = itk::RGBPixel<unsigned char>;
using ImageType = itk::Image<PixelType, 2>;

static void
CreateImage(ImageType::Pointer image);

int
main(int argc, char * argv[])
{
  auto                image = ImageType::New();
  ImageType::SizeType cropSize;
  std::stringstream   desc;

  if (argc > 1)
  {
    image = itk::ReadImage<ImageType>(argv[1]);
    if (argc > 2)
    {
      cropSize[0] = std::stoi(argv[2]);
      cropSize[1] = std::stoi(argv[3]);
    }
    desc << itksys::SystemTools::GetFilenameName(argv[1]);
  }
  else
  {
    CreateImage(image);
    cropSize[0] = 10;
    cropSize[1] = 14;
    desc << "Synthetic image";
  }

  using CropImageFilterType = itk::CropImageFilter<ImageType, ImageType>;

  auto cropFilter = CropImageFilterType::New();
  cropFilter->SetInput(image);
  // The SetBoundaryCropSize( cropSize ) method specifies the size of
  // the boundary to be cropped at both the uppper & lower ends of the
  // image eg. cropSize pixels will be removed at both upper & lower
  // extents

  cropFilter->SetBoundaryCropSize(cropSize);

  // The below two lines are equivalent to the above line:
  // cropFilter->SetUpperBoundaryCropSize(cropSize);
  // cropFilter->SetLowerBoundaryCropSize(cropSize);

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddRGBImage(image.GetPointer(), true, desc.str());

  std::stringstream desc2;
  desc2 << "CropImageFilter, crop size = {" << cropSize[0] << ", " << cropSize[1] << "}";
  viewer.AddRGBImage(cropFilter->GetOutput(), true, desc2.str());

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
  unsigned int        NumRows = 200;
  unsigned int        NumCols = 300;
  size[0] = NumRows;
  size[1] = NumCols;

  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(itk::NumericTraits<ImageType::PixelType>::ZeroValue());

  PixelType rgbPixel;
  rgbPixel[0] = 200;
  rgbPixel[1] = 200;
  rgbPixel[2] = 200;

  // Make a rectangle, centered at (100,150) with sides 160 & 240
  // This provides a 20 x 30 border around the square for the crop filter to remove
  for (unsigned int r = 20; r < 180; ++r)
  {
    for (unsigned int c = 30; c < 270; ++c)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, rgbPixel);
    }
  }
}
