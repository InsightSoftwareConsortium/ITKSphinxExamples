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

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCannyEdgeDetectionImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 6)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << "<InputImage> <OutputImage> ";
    std::cerr << "<Variance> <LowerThreshold> <UpperThreshold>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;
  using InputPixelType = float;
  using OutputPixelType = unsigned char;

  const char *         inputImage = argv[1];
  const char *         outputImage = argv[2];
  const InputPixelType variance = std::stod(argv[3]);
  const InputPixelType lowerThreshold = std::stod(argv[4]);
  const InputPixelType upperThreshold = std::stod(argv[5]);

  using InputImageType = itk::Image<InputPixelType, Dimension>;
  using OutputImageType = itk::Image<OutputPixelType, Dimension>;

  const auto input = itk::ReadImage<InputImageType>(inputImage);

  using FilterType = itk::CannyEdgeDetectionImageFilter<InputImageType, InputImageType>;
  auto filter = FilterType::New();
  filter->SetInput(input);
  filter->SetVariance(variance);
  filter->SetLowerThreshold(lowerThreshold);
  filter->SetUpperThreshold(upperThreshold);

  using RescaleType = itk::RescaleIntensityImageFilter<InputImageType, OutputImageType>;
  auto rescaler = RescaleType::New();
  rescaler->SetInput(filter->GetOutput());
  rescaler->SetOutputMinimum(0);
  rescaler->SetOutputMaximum(255);

  try
  {
    itk::WriteImage(rescaler->GetOutput(), outputImage);
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
