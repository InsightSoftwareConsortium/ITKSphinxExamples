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

namespace
{
using ImageType = itk::Image<unsigned char, 2>;
}

ImageType::Pointer
ReturnSmartPointer()
{
  auto                image = ImageType::New();
  itk::Index<2>       corner = { { 0, 0 } };
  itk::Size<2>        size = { { 10, 10 } };
  itk::ImageRegion<2> region(corner, size);
  image->SetRegions(region);
  image->Allocate();

  return image;
}

ImageType *
ReturnPointer()
{
  auto                image = ImageType::New();
  itk::Index<2>       corner = { { 0, 0 } };
  itk::Size<2>        size = { { 10, 10 } };
  itk::ImageRegion<2> region(corner, size);
  image->SetRegions(region);
  image->Allocate();

  return image;
}

int
main()
{
  {
    // This is how it should be done.
    ImageType::Pointer smartPointer = ReturnSmartPointer();
    std::cout << smartPointer->GetLargestPossibleRegion() << std::endl;
  }

  {
    ImageType * pointer = ReturnPointer();
    (void)pointer;
    // This crashes the program because the smart pointer created in the function goes out of scope and gets deleted
    // because it is returned as a normal pointer.
    // std::cout << pointer->GetLargestPossibleRegion() << std::endl;
    pointer = nullptr; // Here to silence warning
  }

  {
    ImageType * pointer = ReturnSmartPointer();
    (void)pointer;
    // This crashes the program because though the function returned a ::Pointer, it was not stored
    // anywhere so the reference count was not increased, so it got deleted.
    // std::cout << pointer->GetLargestPossibleRegion() << std::endl;
    pointer = nullptr; // Here to silence warning
  }

  {
    // I thought this might also work, but it does not (crash).
    // My reasoning was that even though you don't return a smart pointer, you assign the object to a smart
    // pointer at return time, so it still has a reference count of 1.
    // ImageType::Pointer smartPointer = ReturnPointer(); // this line causes a 'glibc error'
    // std::cout << smartPointer->GetLargestPossibleRegion() << std::endl;
  }

  return 0;
}
