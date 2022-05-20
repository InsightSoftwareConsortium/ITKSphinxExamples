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

#include "itkAbsImageFilter.h"
#include "itkImage.h"

template <class TImage>
void
CreateImage(typename TImage::Pointer image)
{
  using ImageType = TImage;
  typename ImageType::IndexType start;
  start.Fill(0);

  typename ImageType::SizeType size;
  size.Fill(2);

  typename ImageType::RegionType region(start, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(-2);
}

int
main()
{
  constexpr unsigned int Dimension = 2;
  using PixelType = double;

  using ImageType = itk::Image<PixelType, Dimension>;

  using FilterType = itk::AbsImageFilter<ImageType, ImageType>;
  auto                filter = FilterType::New();
  FilterType::Pointer filter2 = dynamic_cast<FilterType *>(filter->CreateAnother().GetPointer());

  auto image = ImageType::New();
  CreateImage<ImageType>(image);

  filter2->SetInput(image);
  filter2->Update();

  itk::Index<Dimension> index;
  index.Fill(0);

  std::cout << filter2->GetOutput()->GetPixel(index) << std::endl;

  return EXIT_SUCCESS;
}
