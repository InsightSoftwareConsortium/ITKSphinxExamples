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

#include "itkMedianImageFilter.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int
main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " <InputImageFile> <OutputImageFile> <radius>" << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];
  const int    radiusValue = std::stoi(argv[3]);

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(inputFileName);

  using FilterType = itk::MedianImageFilter<ImageType, ImageType>;
  FilterType::Pointer medianFilter = FilterType::New();

  FilterType::InputSizeType radius;
  radius.Fill(radiusValue);

  medianFilter->SetRadius(radius);
  medianFilter->SetInput(input);

  try
  {
    itk::WriteImage(medianFilter->GetOutput(), outputFileName);
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
