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
#include "itkImageBufferRange.h"
#include "itkIndexRange.h"
#include "itkNumericTraits.h"

#include <cassert>
#include <numeric> // For iota

namespace
{
// Creates an image with sequentially increasing pixel values (0, 1, 2, ...).
template <typename TImage>
typename TImage::Pointer
CreateImageWithSequentiallyIncreasingPixelValues(const typename TImage::RegionType & region)
{
  using PixelType = typename TImage::PixelType;

  const auto image = TImage::New();
  image->SetRegions(region);
  image->Allocate();

  const itk::ImageBufferRange<TImage> imageBufferRange(*image);
  std::iota(imageBufferRange.begin(), imageBufferRange.end(), PixelType{ 0 });

  return image;
}


// Prints all pixel values with their N-dimensional indices.
template <typename TImage>
void
PrintPixelValues(const TImage & image)
{
  constexpr unsigned int                      Dimension{ TImage::ImageDimension };
  const itk::ImageRegion<Dimension>           region = image.GetBufferedRegion();
  const itk::ImageRegionIndexRange<Dimension> indexRange(region);
  const itk::ImageBufferRange<const TImage>   imageBufferRange(image);

  using PixelType = typename TImage::PixelType;
  using PrintType = typename itk::NumericTraits<PixelType>::PrintType;

  std::cout << "Region index: " << region.GetIndex() << "; Region size: " << region.GetSize() << "\n\n";

  auto indexIterator = indexRange.cbegin();

  for (const PixelType pixel : imageBufferRange)
  {
    const itk::Index<Dimension> index = *indexIterator;
    std::cout << "Pixel index: " << index << "; Pixel value: " << PrintType{ pixel } << '\n';
    ++indexIterator;
  }

  assert(indexIterator == indexRange.cend());
}

} // namespace


int
main()
{
  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType>;
  using RegionType = ImageType::RegionType;

  const RegionType              region(itk::MakeIndex(100, 200), itk::MakeSize(4, 5));
  const ImageType::ConstPointer image = CreateImageWithSequentiallyIncreasingPixelValues<ImageType>(region);
  PrintPixelValues(*image);
}
