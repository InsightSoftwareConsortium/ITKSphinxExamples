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
main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  outputImageFile" << std::endl;
    return EXIT_FAILURE;
  }

  // We select the data type used to represent the image pixels. We
  // assume that the external block of memory uses the same data type to
  // represent the pixels.
  using PixelType = unsigned char;
  constexpr unsigned int Dimension = 2;

  using ImageType = itk::Image<PixelType, Dimension>;
  using ImportFilterType = itk::ImportImageFilter<PixelType, Dimension>;
  auto importFilter = ImportFilterType::New();
  // This filter requires the user to specify the size of the image to be
  // produced as output.  The `SetRegion()` method is used to this end.
  // The image size should exactly match the number of pixels available in the
  // locally allocated buffer.
  ImportFilterType::SizeType size;

  size[0] = 200; // size along X
  size[1] = 200; // size along Y

  ImportFilterType::IndexType start{};

  ImportFilterType::RegionType region;
  region.SetIndex(start);
  region.SetSize(size);

  importFilter->SetRegion(region);

  const itk::SpacePrecisionType origin[Dimension] = { 0.0, 0.0 };
  importFilter->SetOrigin(origin);
  const itk::SpacePrecisionType spacing[Dimension] = { 1.0, 1.0 };
  importFilter->SetSpacing(spacing);
  // Next we allocate the memory block containing the pixel data to be
  // passed to the `ImportImageFilter`. Note that we use exactly the
  // same size that was specified with the `SetRegion()` method. In a
  // practical application, you may get this buffer from some other library
  // using a different data structure to represent the images.
  const unsigned int numberOfPixels = size[0] * size[1];
  auto *             localBuffer = new PixelType[numberOfPixels];
  constexpr double   radius = 80.0;
  // Here we fill up the buffer with a binary sphere.
  const double radius2 = radius * radius;
  PixelType *  it = localBuffer;

  for (unsigned int y = 0; y < size[1]; ++y)
  {
    const double dy = static_cast<double>(y) - static_cast<double>(size[1]) / 2.0;
    for (unsigned int x = 0; x < size[0]; ++x)
    {
      const double dx = static_cast<double>(x) - static_cast<double>(size[0]) / 2.0;
      const double d2 = dx * dx + dy * dy;
      *it++ = (d2 < radius2) ? 255 : 0;
    }
  }
  // The buffer is passed to the ImportImageFilter with the
  // `SetImportPointer()` method. Note that the last argument of this method
  // specifies who will be responsible for deleting the memory block once it
  // is no longer in use. A `true` value, will allow the
  // filter to delete the memory block upon destruction of the import filter.
  //
  // For the `ImportImageFilter` to appropriately delete the
  // memory block, the memory must be allocated with the C++
  // `new()` operator. Memory allocated with other memory
  // allocation mechanisms, such as C `malloc` or `calloc`, will not
  // be deleted properly by the `ImportImageFilter`. In
  // other words, it is the application programmer's responsibility
  // to ensure that `ImportImageFilter` is only given
  // permission to delete the C++ `new` operator-allocated memory.
  const bool importImageFilterWillOwnTheBuffer = true;
  importFilter->SetImportPointer(localBuffer, numberOfPixels, importImageFilterWillOwnTheBuffer);
  // Finally, we can connect the output of this filter to a pipeline.
  // For simplicity we just use a writer here, but it could be any other filter.
  using WriterType = itk::ImageFileWriter<ImageType>;
  auto writer = WriterType::New();

  writer->SetFileName(argv[1]);
  writer->SetInput(importFilter->GetOutput());
  try
  {
    writer->Update();
  }
  catch (const itk::ExceptionObject & exp)
  {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << exp << std::endl;
    return EXIT_FAILURE;
  }

  // Note that we do not call `delete` on the buffer since we pass
  // `true` as the last argument of `SetImportPointer()`. Now the
  // buffer is owned by the `ImportImageFilter`.

  return EXIT_SUCCESS;
}
