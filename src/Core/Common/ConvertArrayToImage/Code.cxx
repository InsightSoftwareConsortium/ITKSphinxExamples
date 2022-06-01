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
#include "itkImportImageFilter.h"

#include "itkImageFileWriter.h"

int
main()
{
  using PixelType = unsigned char;
  constexpr unsigned int Dimension = 3;
  using ImportFilterType = itk::ImportImageFilter<PixelType, Dimension>;

  auto importFilter = ImportFilterType::New();

  ImportFilterType::SizeType size;

  size[0] = 200; // size along X
  size[1] = 200; // size along Y
  size[2] = 200; // size along Z

  ImportFilterType::IndexType start;
  start.Fill(0);

  ImportFilterType::RegionType region;
  region.SetIndex(start);
  region.SetSize(size);

  importFilter->SetRegion(region);

  double origin[Dimension];
  origin[0] = 0.0; // X coordinate
  origin[1] = 0.0; // Y coordinate
  origin[2] = 0.0; // Z coordinate

  importFilter->SetOrigin(origin);

  double spacing[Dimension];
  spacing[0] = 1.0; // along X direction
  spacing[1] = 1.0; // along Y direction
  spacing[2] = 1.0; // along Z direction

  importFilter->SetSpacing(spacing);

  const unsigned int numberOfPixels = size[0] * size[1] * size[2];
  auto *             localBuffer = new PixelType[numberOfPixels];

  constexpr double radius = 80.0;

  const double radius2 = radius * radius;
  PixelType *  it = localBuffer;

  for (unsigned int z = 0; z < size[2]; ++z)
  {
    const double dz = static_cast<double>(z) - static_cast<double>(size[2]) / 2.0;
    for (unsigned int y = 0; y < size[1]; ++y)
    {
      const double dy = static_cast<double>(y) - static_cast<double>(size[1]) / 2.0;
      for (unsigned int x = 0; x < size[0]; ++x)
      {
        const double dx = static_cast<double>(x) - static_cast<double>(size[0]) / 2.0;
        const double d2 = dx * dx + dy * dy + dz * dz;
        *it++ = (d2 < radius2) ? 255 : 0;
      }
    }
  }

  const bool importImageFilterWillOwnTheBuffer = true;
  importFilter->SetImportPointer(localBuffer, numberOfPixels, importImageFilterWillOwnTheBuffer);

  itk::WriteImage(importFilter->GetOutput(), "test.mhd");

  return EXIT_SUCCESS;
}
