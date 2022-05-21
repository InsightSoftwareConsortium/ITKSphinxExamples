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
#include "itkImageRegionIterator.h"
#include "itkBinaryImageToLabelMapFilter.h"

using ImageType = itk::Image<unsigned char, 2>;
static void
CreateImage(ImageType::Pointer image);

int
main()
{
  auto image = ImageType::New();
  CreateImage(image);

  using BinaryImageToLabelMapFilterType = itk::BinaryImageToLabelMapFilter<ImageType>;
  auto binaryImageToLabelMapFilter = BinaryImageToLabelMapFilterType::New();
  binaryImageToLabelMapFilter->SetInput(image);
  binaryImageToLabelMapFilter->Update();

  // The output of this filter is an itk::LabelMap, which contains itk::LabelObject's
  std::cout << "There are " << binaryImageToLabelMapFilter->GetOutput()->GetNumberOfLabelObjects() << " objects."
            << std::endl;

  std::vector<unsigned long> labelsToRemove;

  std::cout << "There are originally " << binaryImageToLabelMapFilter->GetOutput()->GetNumberOfLabelObjects()
            << " objects." << std::endl;

  // Note: do NOT remove the labels inside the loop! The IDs are stored such that they will change when one is deleted.
  // Instead, mark all of the labels to be removed first and then remove them all together.
  for (unsigned int i = 0; i < binaryImageToLabelMapFilter->GetOutput()->GetNumberOfLabelObjects(); ++i)
  {
    // Get the ith region
    BinaryImageToLabelMapFilterType::OutputImageType::LabelObjectType * labelObject =
      binaryImageToLabelMapFilter->GetOutput()->GetNthLabelObject(i);
    // std::cout << "Region " << i << " has " << labelObject->Size() << " pixels." << std::endl;

    // Mark every other label to be removed
    if (i % 2 == 0)
    {
      labelsToRemove.push_back(labelObject->GetLabel());
    }
  }

  std::cout << "Removing " << labelsToRemove.size() << " objects." << std::endl;
  // Remove all regions that were marked for removal.
  for (unsigned long i : labelsToRemove)
  {
    binaryImageToLabelMapFilter->GetOutput()->RemoveLabel(i);
  }

  std::cout << "There are " << binaryImageToLabelMapFilter->GetOutput()->GetNumberOfLabelObjects()
            << " objects remaining." << std::endl;


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

  ImageType::RegionType region(start, size);
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  // Make line of non-touching diagonal pixels
  for (unsigned int i = 0; i < 20; i += 2)
  {
    itk::Index<2> pixel;
    pixel[0] = i;
    pixel[1] = i;
    image->SetPixel(pixel, 255);
  }
}
