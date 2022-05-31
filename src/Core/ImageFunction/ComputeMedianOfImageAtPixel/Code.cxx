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
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include "itkMedianImageFunction.h"

using UnsignedCharImageType = itk::Image<unsigned char, 2>;

void
CreateImage(UnsignedCharImageType::Pointer image);

int
main()
{
  auto image = UnsignedCharImageType::New();
  CreateImage(image);

  using MedianImageFunctionType = itk::MedianImageFunction<UnsignedCharImageType>;
  auto medianImageFunction = MedianImageFunctionType::New();
  medianImageFunction->SetInputImage(image);

  itk::Index<2> index;
  index.Fill(10);
  std::cout << "Median at " << index << " is " << static_cast<int>(medianImageFunction->EvaluateAtIndex(index))
            << std::endl;
  return EXIT_SUCCESS;
}

void
CreateImage(UnsignedCharImageType::Pointer image)
{
  itk::Index<2> start;
  start.Fill(0);

  itk::Size<2> size;
  size.Fill(100);

  itk::ImageRegion<2> region(start, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  itk::ImageRegionIterator<UnsignedCharImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] >= 50 && imageIterator.GetIndex()[1] >= 50 && imageIterator.GetIndex()[0] <= 70 &&
        imageIterator.GetIndex()[1] <= 70)
    {
      imageIterator.Set(255);
    }

    ++imageIterator;
  }

  itk::WriteImage(image, "input.png");
}
