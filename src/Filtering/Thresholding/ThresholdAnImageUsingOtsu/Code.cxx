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

#include "itkImageFileReader.h"
#include "itkOtsuMultipleThresholdsImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkImageFileWriter.h"

int
main(int argc, char * argv[])
{
  if (argc < 6)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << std::endl;
    std::cerr << " <InputImage> <OutputImage> <NumberOfBins>";
    std::cerr << " <NumberOfThresholds> <LabelOffset>" << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;
  using PixelType = unsigned char;
  using SizeType = itk::SizeValueType;

  const char * InputImage = argv[1];
  const char * OutputImage = argv[2];

  const auto NumberOfHistogramBins = static_cast<SizeType>(atoi(argv[3]));
  const auto NumberOfThresholds = static_cast<SizeType>(atoi(argv[4]));
  const auto LabelOffset = static_cast<PixelType>(atoi(argv[5]));

  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(InputImage);

  using FilterType = itk::OtsuMultipleThresholdsImageFilter<ImageType, ImageType>;
  auto filter = FilterType::New();
  filter->SetInput(input);
  filter->SetNumberOfHistogramBins(NumberOfHistogramBins);
  filter->SetNumberOfThresholds(NumberOfThresholds);
  filter->SetLabelOffset(LabelOffset);

  FilterType::ThresholdVectorType thresholds = filter->GetThresholds();

  std::cout << "Thresholds:" << std::endl;

  for (double threshold : thresholds)
  {
    std::cout << threshold << std::endl;
  }

  std::cout << std::endl;

  using RescaleType = itk::RescaleIntensityImageFilter<ImageType, ImageType>;
  auto rescaler = RescaleType::New();
  rescaler->SetInput(filter->GetOutput());
  rescaler->SetOutputMinimum(0);
  rescaler->SetOutputMaximum(255);

  try
  {
    itk::WriteImage(rescaler->GetOutput(), OutputImage);
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
