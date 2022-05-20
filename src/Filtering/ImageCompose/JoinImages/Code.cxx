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
#include "itkRescaleIntensityImageFilter.h"
#include "itkJoinImageFilter.h"
#include "itkVectorImageToImageAdaptor.h"

using ImageType = itk::Image<unsigned char, 2>;

static void
CreateImage(ImageType::Pointer image, unsigned char value);

int
main()
{
  auto image1 = ImageType::New();
  CreateImage(image1, 0);

  auto image2 = ImageType::New();
  CreateImage(image2, 10);

  using JoinImageFilterType = itk::JoinImageFilter<ImageType, ImageType>;

  auto joinFilter = JoinImageFilterType::New();
  joinFilter->SetInput1(image1);
  joinFilter->SetInput2(image2);
  joinFilter->Update();

  itk::Index<2> index;
  index[0] = 0;
  index[1] = 0;

  std::cout << static_cast<int>(joinFilter->GetOutput()->GetPixel(index)[0]) << std::endl;
  std::cout << static_cast<int>(joinFilter->GetOutput()->GetPixel(index)[1]) << std::endl;

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image, unsigned char value)
{
  // Create an image
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(100);

  ImageType::RegionType region(start, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(value);
}
