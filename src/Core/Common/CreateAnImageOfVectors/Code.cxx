/*=========================================================================
 *
 *  Copyright Insight Software Consortium
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

#include "itkVector.h"
#include "itkImage.h"

int
main(int, char *[])
{
  using PixelType = itk::Vector<float, 3>;
  using ImageType = itk::Image<PixelType, 3>;

  // Then the image object can be created
  ImageType::Pointer image = ImageType::New();

  // The image region should be initialized
  const ImageType::IndexType start = { { 0, 0, 0 } };      // First index at {X,Y,Z}
  const ImageType::SizeType  size = { { 200, 200, 200 } }; // Size of {X,Y,Z}

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  // Pixel data is allocated
  image->SetRegions(region);
  image->Allocate();

  // The image buffer is initialized to a particular value
  ImageType::PixelType initialValue;

  // A vector can initialize all its components to the
  // same value by using the Fill() method.
  initialValue.Fill(0.0);

  // Now the image buffer can be initialized with this
  // vector value.
  image->FillBuffer(initialValue);

  const ImageType::IndexType pixelIndex = { { 27, 29, 37 } }; // Position {X,Y,Z}


  ImageType::PixelType pixelValue;
  pixelValue[0] = 1.345; // x component
  pixelValue[1] = 6.841; // y component
  pixelValue[2] = 3.295; // x component

  image->SetPixel(pixelIndex, pixelValue);

  ImageType::PixelType value = image->GetPixel(pixelIndex);

  std::cout << value << std::endl;


  return EXIT_SUCCESS;
}
