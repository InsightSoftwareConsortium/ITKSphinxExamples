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
#include "itkImageFileWriter.h"

#include "ImageFilterY.h"

template <typename TImage>
static void
CreateImage(TImage * const image);

int
main()
{
  // Setup types
  using ImageType = itk::Image<unsigned char, 2>;
  using FilterType = itk::ImageFilter<ImageType>;

  auto image = ImageType::New();
  CreateImage(image.GetPointer());

  std::cout << "Input:" << std::endl;
  std::cout << image->GetLargestPossibleRegion() << std::endl;
  // Create and the filter
  auto filter = FilterType::New();
  filter->SetInput(image);
  filter->Update();

  std::cout << "Input:" << std::endl;
  std::cout << filter->GetOutput()->GetLargestPossibleRegion() << std::endl;

  using WriterType = itk::ImageFileWriter<ImageType>;
  auto writer = WriterType::New();
  writer->SetFileName("Output.png");
  writer->SetInput(filter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}

template <typename TImage>
void
CreateImage(TImage * const image)
{
  // Create an image with 2 connected components
  typename TImage::IndexType corner = { { 0, 0 } };

  unsigned int              NumRows = 200;
  unsigned int              NumCols = 300;
  typename TImage::SizeType size = { { NumRows, NumCols } };

  typename TImage::RegionType region(corner, size);

  image->SetRegions(region);
  image->Allocate();

  // Make another square
  for (unsigned int r = 40; r < 100; ++r)
  {
    for (unsigned int c = 40; c < 100; ++c)
    {
      typename TImage::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 15);
    }
  }
}
