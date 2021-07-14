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
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include "itkBinaryImageToLabelMapFilter.h"

using ImageType = itk::Image<unsigned char, 2>;
static void
CreateImage(ImageType::Pointer image);

int
main(int, char *[])
{
  ImageType::Pointer image = ImageType::New();
  CreateImage(image);

  using BinaryImageToLabelMapFilterType = itk::BinaryImageToLabelMapFilter<ImageType>;
  BinaryImageToLabelMapFilterType::Pointer binaryImageToLabelMapFilter = BinaryImageToLabelMapFilterType::New();
  binaryImageToLabelMapFilter->SetInput(image);
  binaryImageToLabelMapFilter->Update();

  // The output of this filter is an itk::LabelMap, which contains itk::LabelObject's
  std::cout << "There are " << binaryImageToLabelMapFilter->GetOutput()->GetNumberOfLabelObjects() << " objects."
            << std::endl;

  // Loop over each region
  for (unsigned int i = 0; i < binaryImageToLabelMapFilter->GetOutput()->GetNumberOfLabelObjects(); i++)
  {
    // Get the ith region
    BinaryImageToLabelMapFilterType::OutputImageType::LabelObjectType * labelObject =
      binaryImageToLabelMapFilter->GetOutput()->GetNthLabelObject(i);

    // Output the pixels composing the region
    for (unsigned int pixelId = 0; pixelId < labelObject->Size(); pixelId++)
    {
      std::cout << "Object " << i << " contains pixel " << labelObject->GetIndex(pixelId) << std::endl;
    }
  }

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  // Create a black image with a white square
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(20);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);
  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image, image->GetLargestPossibleRegion());

  // Make a square
  while (!imageIterator.IsAtEnd())
  {
    if ((imageIterator.GetIndex()[0] > 5 && imageIterator.GetIndex()[0] < 10) &&
        (imageIterator.GetIndex()[1] > 5 && imageIterator.GetIndex()[1] < 10))
    {
      imageIterator.Set(255);
    }
    else
    {
      imageIterator.Set(0);
    }

    ++imageIterator;
  }

  itk::WriteImage(image, "image.png");
}
