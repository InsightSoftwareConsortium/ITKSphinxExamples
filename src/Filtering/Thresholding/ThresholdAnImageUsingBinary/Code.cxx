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
#include "itkImage.h"
#include "itkBinaryThresholdImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc < 7)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << std::endl;
    std::cerr << " <InputImage> <OutputImage> <LowerThreshold>";
    std::cerr << " <UpperThreshold> <OutsideValue> <InsideValue>" << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;
  using PixelType = unsigned char;

  const char * InputImage = argv[1];
  const char * OutputImage = argv[2];

  const auto LowerThreshold = static_cast<PixelType>(atoi(argv[3]));
  const auto UpperThreshold = static_cast<PixelType>(atoi(argv[4]));
  const auto OutsideValue = static_cast<PixelType>(atoi(argv[5]));
  const auto InsideValue = static_cast<PixelType>(atoi(argv[6]));

  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(InputImage);

  using FilterType = itk::BinaryThresholdImageFilter<ImageType, ImageType>;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(input);
  filter->SetLowerThreshold(LowerThreshold);
  filter->SetUpperThreshold(UpperThreshold);
  filter->SetOutsideValue(OutsideValue);
  filter->SetInsideValue(InsideValue);

  try
  {
    itk::WriteImage(filter->GetOutput(), OutputImage);
  }
  catch (itk::ExceptionObject & e)
  {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
