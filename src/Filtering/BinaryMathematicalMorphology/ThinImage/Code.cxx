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
#include "itkBinaryThinningImageFilter.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"

using ImageType = itk::Image<unsigned char, 2>;

static void
CreateImage(ImageType::Pointer image);

int
main(int argc, char * argv[])
{
  ImageType::Pointer image = ImageType::New();
  if (argc == 2)
  {
    image = itk::ReadImage<ImageType>(argv[1]);
  }
  else
  {
    CreateImage(image);
    itk::WriteImage(image, "Input.png");
  }

  using BinaryThinningImageFilterType = itk::BinaryThinningImageFilter<ImageType, ImageType>;
  BinaryThinningImageFilterType::Pointer binaryThinningImageFilter = BinaryThinningImageFilterType::New();
  binaryThinningImageFilter->SetInput(image);
  binaryThinningImageFilter->Update();

  // Rescale the image so that it can be seen (the output is 0 and 1, we want 0 and 255)
  using RescaleType = itk::RescaleIntensityImageFilter<ImageType, ImageType>;
  RescaleType::Pointer rescaler = RescaleType::New();
  rescaler->SetInput(binaryThinningImageFilter->GetOutput());
  rescaler->SetOutputMinimum(0);
  rescaler->SetOutputMaximum(255);
  rescaler->Update();

  itk::WriteImage(rescaler->GetOutput(), "Output.png");

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  // Create an image
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(100);

  ImageType::RegionType region(start, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  // Draw a 5 pixel wide line
  for (unsigned int i = 20; i < 80; ++i)
  {
    for (unsigned int j = 50; j < 55; ++j)
    {
      itk::Index<2> index;
      index[0] = i;
      index[1] = j;
      image->SetPixel(index, 255);
    }
  }
}
