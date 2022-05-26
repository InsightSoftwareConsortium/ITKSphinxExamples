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

#include "itkConnectedImageNeighborhoodShape.h"
#include "itkImage.h"
#include "itkImageBufferRange.h"
#include "itkImageNeighborhoodOffsets.h"
#include "itkRectangularImageNeighborhoodShape.h"
#include "itkShapedImageNeighborhoodRange.h"

#include <array>
#include <cassert>
#include <numeric> // For iota
#include <ios>     // For hex

namespace
{
constexpr unsigned int Dimension{ 2 };
using OffsetType = itk::Offset<Dimension>;

// Print the specified offsets of a neighborhood shape. Also prints the pixel values of a small image for which such a
// shaped neigborhood located at the image center is filled with consecutive values, 1, 2, 3, ..., N.
template <typename TOffsets>
void
PrintImageNeighborhoodShape(const TOffsets & offsets)
{
  std::cout << "  ";

  for (const OffsetType & offset : offsets)
  {
    std::cout << offset << ' ';
  }

  using ImageType = itk::Image<int>;
  const auto             image = ImageType::New();
  constexpr unsigned int imageSize{ 7 };
  image->SetRegions(ImageType::SizeType::Filled(imageSize));
  image->Allocate(true);

  const auto                                         centerIndex = ImageType::IndexType::Filled(imageSize / 2);
  const itk::ShapedImageNeighborhoodRange<ImageType> shapedImageNeighborhoodRange(*image, centerIndex, offsets);

  // Set the values of the pixels in the "shaped neighborhood" of the image center to 1, 2, 3, ..., N, consecutively.
  std::iota(shapedImageNeighborhoodRange.begin(), shapedImageNeighborhoodRange.end(), 1);

  std::cout << "\n\n";
  const std::ios_base::fmtflags flags(std::cout.flags());
  std::cout << std::hex << std::uppercase;

  const itk::ImageBufferRange<const ImageType> imageBufferRange(*image);
  auto                                         imageBufferIterator = imageBufferRange.cbegin();

  for (int y{ 0 }; y < imageSize; ++y)
  {
    std::cout << "  ";

    for (int x{ 0 }; x < imageSize; ++x)
    {
      std::cout << *imageBufferIterator << ' ';
      ++imageBufferIterator;
    }
    std::cout << '\n';
  }
  std::cout.flags(flags);
  std::cout << '\n';
}

} // namespace


int
main()
{
  const std::array<OffsetType, 3> offsets = { { { { 0, -1 } }, { { 0, 1 } }, { { 1, 1 } } } };
  std::cout << "Shape of some arbitrary offsets:\n\n";
  PrintImageNeighborhoodShape(offsets);

  const bool   includeCenterPixel = false;
  const size_t maximumCityblockDistance = 1;
  std::cout << "4-connected neighborhood shape (excluding the center pixel) with maximumCityblockDistance = "
            << maximumCityblockDistance << ":\n\n";

  // GenerateConnectedImageNeighborhoodShapeOffsets returns an std::array of offsets.
  const auto connectedImageNeighborhoodShapeOffsets =
    itk::GenerateConnectedImageNeighborhoodShapeOffsets<Dimension, maximumCityblockDistance, includeCenterPixel>();
  PrintImageNeighborhoodShape(connectedImageNeighborhoodShapeOffsets);

  const itk::Size<Dimension> radius = { { 1, 2 } };
  std::cout << "Rectangular shape of radius " << radius << ":\n\n";

  // GenerateRectangularImageNeighborhoodOffsets returns an std::vector of offsets.
  const auto rectangularImageNeighborhoodOffsets = itk::GenerateRectangularImageNeighborhoodOffsets(radius);
  PrintImageNeighborhoodShape(rectangularImageNeighborhoodOffsets);
}
