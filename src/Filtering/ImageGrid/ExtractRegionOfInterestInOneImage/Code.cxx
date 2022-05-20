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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRegionOfInterestImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 7)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << " <start x> <end x> <start y> <end y>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  const auto startx = static_cast<itk::IndexValueType>(std::stoi(argv[3]));
  const auto endx = static_cast<itk::IndexValueType>(std::stoi(argv[4]));

  const auto starty = static_cast<itk::IndexValueType>(std::stoi(argv[5]));
  const auto endy = static_cast<itk::IndexValueType>(std::stoi(argv[6]));

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(inputFileName);

  ImageType::IndexType start;
  start[0] = startx;
  start[1] = starty;

  ImageType::IndexType end;
  end[0] = endx;
  end[1] = endy;

  ImageType::RegionType region;
  region.SetIndex(start);
  region.SetUpperIndex(end);

  using FilterType = itk::RegionOfInterestImageFilter<ImageType, ImageType>;
  auto filter = FilterType::New();
  filter->SetInput(input);
  filter->SetRegionOfInterest(region);

  try
  {
    itk::WriteImage(filter->GetOutput(), outputFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
