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
#include "itkTileImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName1> <InputFileName2> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }
  const char * inputFileName1 = argv[1];
  const char * inputFileName2 = argv[2];
  const char * outputFileName = argv[3];

  constexpr unsigned int Dimension = 3;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input1 = itk::ReadImage<ImageType>(inputFileName1);
  const auto input2 = itk::ReadImage<ImageType>(inputFileName2);

  using TileFilterType = itk::TileImageFilter<ImageType, ImageType>;
  auto tileFilter = TileFilterType::New();
  tileFilter->SetInput(0, input1);
  tileFilter->SetInput(1, input2);
  TileFilterType::LayoutArrayType layout;
  layout[0] = 1;
  layout[1] = 1;
  layout[2] = 2;
  tileFilter->SetLayout(layout);

  try
  {
    itk::WriteImage(tileFilter->GetOutput(), outputFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
