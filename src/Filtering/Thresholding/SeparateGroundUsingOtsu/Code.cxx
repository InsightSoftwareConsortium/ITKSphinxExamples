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
#include "itkOtsuThresholdImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageRegionIterator.h"
#include "itkNumericTraits.h"

#include "itksys/SystemTools.hxx"
#include <sstream>

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

namespace
{
using PixelType = unsigned char;
using ImageType = itk::Image<PixelType, 2>;
} // namespace

static void
CreateImage(ImageType::Pointer image);

int
main(int argc, char * argv[])
{
  ImageType::Pointer image;
  if (argc < 2)
  {
    image = ImageType::New();
    CreateImage(image.GetPointer());
  }
  else
  {
    image = itk::ReadImage<ImageType>(argv[1]);
  }

  using FilterType = itk::OtsuThresholdImageFilter<ImageType, ImageType>;
  auto otsuFilter = FilterType::New();
  otsuFilter->SetInput(image);
  otsuFilter->Update(); // To compute threshold

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(
    image.GetPointer(), true, argc > 1 ? itksys::SystemTools::GetFilenameName(argv[1]) : "Generated image");

  std::stringstream desc;
  desc << "Otsu Threshold: " << itk::NumericTraits<FilterType::InputPixelType>::PrintType(otsuFilter->GetThreshold());
  viewer.AddImage(otsuFilter->GetOutput(), true, desc.str());

  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  // Create an image
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(100);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  // Make the whole image white
  itk::ImageRegionIterator<ImageType> iterator(image, image->GetLargestPossibleRegion());

  /*
   //Create a square
  while(!iterator.IsAtEnd())
    {
    iterator.Set(255);
    ++iterator;
    }
  */
}
