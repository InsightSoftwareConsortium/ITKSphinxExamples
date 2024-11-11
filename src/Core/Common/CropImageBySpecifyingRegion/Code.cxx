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
// This is different from CropImageFilter only in the way
// that the region to crop is specified.
#include "itkImage.h"
#include <itkExtractImageFilter.h>

int
main()
{
  using ImageType = itk::Image<unsigned char, 2>;

  ImageType::IndexType start{};

  auto size = ImageType::SizeType::Filled(10);

  ImageType::RegionType region(start, size);

  auto image = ImageType::New();
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(5);

  std::cout << "Image largest region: " << image->GetLargestPossibleRegion() << std::endl;

  auto desiredStart = ImageType::IndexType::Filled(3);

  auto desiredSize = ImageType::SizeType::Filled(4);

  ImageType::RegionType desiredRegion(desiredStart, desiredSize);

  std::cout << "desiredRegion: " << desiredRegion << std::endl;

  using FilterType = itk::ExtractImageFilter<ImageType, ImageType>;
  auto filter = FilterType::New();
  filter->SetExtractionRegion(desiredRegion);
  filter->SetInput(image);
#if ITK_VERSION_MAJOR >= 4
  filter->SetDirectionCollapseToIdentity(); // This is required.
#endif
  filter->Update();

  ImageType::Pointer output = filter->GetOutput();
  output->DisconnectPipeline();
  output->FillBuffer(2);

  auto index = itk::Index<2>::Filled(5);

  std::cout << "new largest region: " << output->GetLargestPossibleRegion() << std::endl;
  std::cout << "new: " << (int)output->GetPixel(index) << std::endl;
  std::cout << "Original: " << (int)image->GetPixel(index) << std::endl;

  return EXIT_SUCCESS;
}
