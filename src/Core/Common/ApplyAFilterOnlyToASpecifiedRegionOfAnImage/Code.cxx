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
#include "itkRandomImageSource.h"
#include "itkDerivativeImageFilter.h"

int
main()
{
  constexpr unsigned int Dimension = 2;
  using PixelType = float;

  using ImageType = itk::Image<PixelType, Dimension>;

  ImageType::SizeType smallSize;
  smallSize.Fill(10);

  ImageType::IndexType index;
  index.Fill(0);

  ImageType::RegionType region(index, smallSize);

  ImageType::SizeType bigSize;
  bigSize.Fill(10000);

  using RandomSourceType = itk::RandomImageSource<ImageType>;
  auto randomImageSource = RandomSourceType::New();
  randomImageSource->SetNumberOfWorkUnits(1); // to produce non-random results
  randomImageSource->SetSize(bigSize);
  randomImageSource->GetOutput()->SetRequestedRegion(smallSize);

  std::cout << "Created random image." << std::endl;

  using DerivativeImageFilterType = itk::DerivativeImageFilter<ImageType, ImageType>;

  auto derivativeFilter = DerivativeImageFilterType::New();
  derivativeFilter->SetInput(randomImageSource->GetOutput());
  derivativeFilter->SetDirection(0); // "x" axis
  derivativeFilter->GetOutput()->SetRequestedRegion(smallSize);
  derivativeFilter->Update();

  std::cout << "Computed derivative." << std::endl;

  return EXIT_SUCCESS;
}
