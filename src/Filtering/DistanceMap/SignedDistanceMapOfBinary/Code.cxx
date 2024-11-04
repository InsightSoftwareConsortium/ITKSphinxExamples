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
#include "itkImageFileReader.h"
#include "itkSignedDanielssonDistanceMapImageFilter.h"

#include "itksys/SystemTools.hxx"
#include <sstream>

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

using UnsignedCharImageType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;

static void
CreateImage(UnsignedCharImageType::Pointer image);

int
main(int argc, char * argv[])
{
  auto image = UnsignedCharImageType::New();
  if (argc < 2)
  {
    CreateImage(image);
  }
  else
  {
    image = itk::ReadImage<UnsignedCharImageType>(argv[1]);
  }

  using SignedDanielssonDistanceMapImageFilterType =
    itk::SignedDanielssonDistanceMapImageFilter<UnsignedCharImageType, FloatImageType>;
  SignedDanielssonDistanceMapImageFilterType::Pointer distanceMapImageFilter =
    SignedDanielssonDistanceMapImageFilterType::New();
  distanceMapImageFilter->SetInput(image);

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(
    image.GetPointer(), true, argc > 1 ? itksys::SystemTools::GetFilenameName(argv[1]) : "Generated image");

  std::stringstream desc;
  desc << "Signed Danielsson Distance";
  viewer.AddImage(distanceMapImageFilter->GetOutput(), true, desc.str());

  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}


void
CreateImage(UnsignedCharImageType::Pointer image)
{
  // Create an image
  itk::Index<2> start{};

  itk::Size<2> size;
  size.Fill(100);

  itk::ImageRegion<2> region(start, size);
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  // Create a line of white pixels
  for (unsigned int i = 40; i < 60; ++i)
  {
    itk::Index<2> pixel;
    pixel.Fill(i);
    image->SetPixel(pixel, 255);
  }
}
