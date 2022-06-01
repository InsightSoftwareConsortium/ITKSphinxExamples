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
#include <itkImage.h>

#include <iostream>

using ImageType = itk::Image<float, 2>;
static void
myStandardPointer(const ImageType *)
{}

static void
mySmartPointer(const ImageType::Pointer)
{}

template <typename TImage>
static void
TemplateSmartPointer(const typename TImage::Pointer)
{}

template <typename TImage>
static void
TemplateStandardPointer(const TImage *)
{}

int
main()
{
  auto                image = ImageType::New();
  itk::Index<2>       corner = { { 0, 0 } };
  itk::Size<2>        size = { { 10, 10 } };
  itk::ImageRegion<2> region(corner, size);
  image->SetRegions(region);
  image->Allocate();

  // A function that accepts a standard pointer can be passed either a standard or a smart pointer
  myStandardPointer(image.GetPointer());
  myStandardPointer(image);

  // A function that accepts a smart pointer can be passed either a standard or a smart pointer
  mySmartPointer(image.GetPointer());
  mySmartPointer(image);

  return 0;
}
