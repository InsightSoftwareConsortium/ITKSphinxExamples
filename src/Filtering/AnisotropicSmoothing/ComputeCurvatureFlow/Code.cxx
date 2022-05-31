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
#include "itkImageFileWriter.h"
#include "itkCurvatureFlowImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 5)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << " <numberOfIterations> <timeStep>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  constexpr unsigned int Dimension = 2;

  using InputPixelType = float;
  using InputImageType = itk::Image<InputPixelType, Dimension>;
  using OutputPixelType = unsigned char;
  using OutputImageType = itk::Image<OutputPixelType, Dimension>;

  const int            numberOfIterations = std::stoi(argv[3]);
  const InputPixelType timeStep = std::stod(argv[4]);

  const auto input = itk::ReadImage<InputImageType>(inputFileName);

  using FilterType = itk::CurvatureFlowImageFilter<InputImageType, InputImageType>;
  auto filter = FilterType::New();
  filter->SetInput(input);
  filter->SetNumberOfIterations(numberOfIterations);
  filter->SetTimeStep(timeStep);

  using RescaleType = itk::RescaleIntensityImageFilter<InputImageType, OutputImageType>;
  auto rescaler = RescaleType::New();
  rescaler->SetInput(filter->GetOutput());
  rescaler->SetOutputMinimum(itk::NumericTraits<OutputPixelType>::min());
  rescaler->SetOutputMaximum(itk::NumericTraits<OutputPixelType>::max());

  try
  {
    itk::WriteImage(rescaler->GetOutput(), outputFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
