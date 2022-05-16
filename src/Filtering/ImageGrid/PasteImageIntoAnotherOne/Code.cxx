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
#include "itkPasteImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 6)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <SourceFileName> <DestinationFileName> <OutputFileName> <start x> <start y>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * sourceFileName = argv[1];
  const char * destinationFileName = argv[2];
  const char * outputFileName = argv[3];

  int startX = std::stoi(argv[4]);
  int startY = std::stoi(argv[5]);

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  ImageType::IndexType index;
  index[0] = startX;
  index[1] = startY;

  const auto source = itk::ReadImage<ImageType>(sourceFileName);
  const auto destination = itk::ReadImage<ImageType>(destinationFileName);

  using FilterType = itk::PasteImageFilter<ImageType, ImageType>;
  FilterType::Pointer filter = FilterType::New();
  filter->SetSourceImage(source);
  filter->SetSourceRegion(source->GetLargestPossibleRegion());
  filter->SetDestinationImage(destination);
  filter->SetDestinationIndex(index);

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
