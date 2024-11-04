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
#include "itkAddPixelAccessor.h"
#include "itkImageAdaptor.h"
#include "itkImageRegionIterator.h"

using ImageType = itk::Image<unsigned int, 2>;

static void
CreateImage(ImageType::Pointer image);

int
main()
{
  auto image = ImageType::New();
  CreateImage(image);

  using AddPixelAccessorType = itk::Accessor::AddPixelAccessor<ImageType::PixelType>;
  using ImageAdaptorType = itk::ImageAdaptor<ImageType, AddPixelAccessorType>;

  auto                 adaptor = ImageAdaptorType::New();
  AddPixelAccessorType addPixelAccessor;


  adaptor->SetImage(image);

  ImageType::IndexType index;
  index[0] = 0;
  index[1] = 0;

  addPixelAccessor.SetValue(5);
  adaptor->SetPixelAccessor(addPixelAccessor);
  std::cout << "addPixelAccessor.SetValue(5)" << std::endl;
  std::cout << "\timage->GetPixel" << index << ": " << image->GetPixel(index) << " adaptor->GetPixel" << index << ": "
            << adaptor->GetPixel(index) << std::endl;

  addPixelAccessor.SetValue(100);
  adaptor->SetPixelAccessor(addPixelAccessor);
  std::cout << "addPixelAccessor.SetValue(100)" << std::endl;
  std::cout << "\timage->GetPixel" << index << ": " << image->GetPixel(index) << " adaptor->GetPixel" << index << ": "
            << adaptor->GetPixel(index) << std::endl;

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  ImageType::IndexType start{};

  ImageType::SizeType size;
  size.Fill(10);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image, image->GetLargestPossibleRegion());

  while (!imageIterator.IsAtEnd())
  {
    imageIterator.Set(20);
    ++imageIterator;
  }
}
