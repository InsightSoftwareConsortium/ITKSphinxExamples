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
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "MultiThreadedImageFilter.h"

template <typename TImage>
static void
CreateImage(TImage * const image);

template <typename TImage>
static void
OutputImage(TImage * const image);

int
main(int, char *[])
{
  // Setup types
  using ImageType = itk::Image<int, 2>;
  using FilterType = itk::MultiThreadedImageFilter<ImageType>;

  ImageType::Pointer image = ImageType::New();
  CreateImage(image.GetPointer());

  // Create and the filter
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(image);
  // filter->SetNumberOfThreads(3); // There is no need to specify this, it is automatically determined
  filter->Update();

  std::cout << "Image after filter: " << std::endl;
  OutputImage(image.GetPointer());

  std::cout << "Output: " << std::endl;
  OutputImage(filter->GetOutput());

  return EXIT_SUCCESS;
}


template <typename TImage>
void
CreateImage(TImage * const image)
{
  // Create an image with 2 connected components
  typename TImage::IndexType corner = { { 0, 0 } };

  //   unsigned int NumRows = 200;
  //   unsigned int NumCols = 300;

  unsigned int              NumRows = 3;
  unsigned int              NumCols = 2;
  typename TImage::SizeType size = { { NumRows, NumCols } };

  typename TImage::RegionType region(corner, size);

  image->SetRegions(region);
  image->Allocate();

  image->FillBuffer(0);
}

template <typename TImage>
void
OutputImage(TImage * const image)
{
  itk::ImageRegionConstIterator<TImage> imageIterator(image, image->GetLargestPossibleRegion());

  while (!imageIterator.IsAtEnd())
  {
    std::cout << imageIterator.Get() << std::endl;

    ++imageIterator;
  }
}
