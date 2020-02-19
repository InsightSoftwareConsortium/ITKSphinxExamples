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
#include "itkImage.h"
#include "itkBinaryPruningImageFilter.h"
#include "itkImageFileReader.h"
#include "itkBinaryBallStructuringElement.h"
#include "itkImageFileWriter.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

template <typename TImage>
void
CreateImage(TImage * const image);

int
main(int argc, char * argv[])
{
  //   std::cerr << "Usage: " << std::endl;
  //   std::cerr << argv[0] << " InputImageFile OutputImageFile [iteration]" << std::endl;

  using ImageType = itk::Image<unsigned char, 2>;
  ImageType::Pointer image;

  unsigned int iteration = 1;

  if (argc < 3)
  {
    image = ImageType::New();
    CreateImage(image.GetPointer());
  }
  else
  {
    using ReaderType = itk::ImageFileReader<ImageType>;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(argv[1]);
    image = reader->GetOutput();
    std::stringstream ssIteration(argv[2]);
  }

  using BinaryPruningImageFilterType = itk::BinaryPruningImageFilter<ImageType, ImageType>;
  BinaryPruningImageFilterType::Pointer pruneFilter = BinaryPruningImageFilterType::New();
  pruneFilter->SetInput(image);
  pruneFilter->SetIteration(iteration);
  pruneFilter->GetOutput();

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(image.GetPointer());
  viewer.AddImage(pruneFilter->GetOutput());
  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}

template <typename TImage>
void
CreateImage(TImage * const image)
{
  // This function creates a 2D image consisting of a black background,
  // a large square of a non-zero pixel value, and a single "erroneous" pixel
  // near the square.
  typename TImage::IndexType corner = { { 0, 0 } };

  typename TImage::SizeType size = { { 200, 200 } };

  typename TImage::RegionType region(corner, size);

  image->SetRegions(region);
  image->Allocate();

  // Make a square
  for (int r = 40; r < 100; r++)
  {
    for (int c = 40; c < 100; c++)
    {
      typename TImage::IndexType pixelIndex = { { r, c } };
      image->SetPixel(pixelIndex, 50);
    }
  }

  typename TImage::IndexType pixelIndex = { { 102, 102 } };

  image->SetPixel(pixelIndex, 50);
}
