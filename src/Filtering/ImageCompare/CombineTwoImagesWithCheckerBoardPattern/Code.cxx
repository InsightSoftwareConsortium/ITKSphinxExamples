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
#include "itkCheckerBoardImageFilter.h"
#include "itkImageFileWriter.h"

int
main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage:" << std::endl;
    std::cerr << argv[0] << " <OutputImage>" << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  ImageType::IndexType start{};

  auto size = ImageType::SizeType::Filled(100);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  auto image1 = ImageType::New();
  image1->SetRegions(region);
  image1->Allocate();
  image1->FillBuffer(0);

  auto image2 = ImageType::New();
  image2->SetRegions(region);
  image2->Allocate();
  image2->FillBuffer(255);

  using CheckerBoardFilterType = itk::CheckerBoardImageFilter<ImageType>;
  auto checkerBoardFilter = CheckerBoardFilterType::New();
  checkerBoardFilter->SetInput1(image1);
  checkerBoardFilter->SetInput2(image2);

  try
  {
    itk::WriteImage(checkerBoardFilter->GetOutput(), argv[1]);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
