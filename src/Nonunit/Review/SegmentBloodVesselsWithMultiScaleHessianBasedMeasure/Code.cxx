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
#include "itkHessianToObjectnessMeasureImageFilter.h"
#include "itkMultiScaleHessianBasedMeasureImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << " [SigmaMinimum] [SigmaMaximum]";
    std::cerr << " [NumberOfSigmaSteps]";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];
  double       sigmaMinimum = 1.0;
  if (argc > 3)
  {
    sigmaMinimum = std::stod(argv[3]);
  }
  double sigmaMaximum = 10.0;
  if (argc > 4)
  {
    sigmaMaximum = std::stod(argv[4]);
  }
  unsigned int numberOfSigmaSteps = 10;
  if (argc > 5)
  {
    numberOfSigmaSteps = std::stoi(argv[5]);
  }

  constexpr unsigned int Dimension = 2;

  using PixelType = float;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(inputFileName);

  using HessianPixelType = itk::SymmetricSecondRankTensor<double, Dimension>;
  using HessianImageType = itk::Image<HessianPixelType, Dimension>;
  using ObjectnessFilterType = itk::HessianToObjectnessMeasureImageFilter<HessianImageType, ImageType>;
  auto objectnessFilter = ObjectnessFilterType::New();
  objectnessFilter->SetBrightObject(false);
  objectnessFilter->SetScaleObjectnessMeasure(false);
  objectnessFilter->SetAlpha(0.5);
  objectnessFilter->SetBeta(1.0);
  objectnessFilter->SetGamma(5.0);

  using MultiScaleEnhancementFilterType =
    itk::MultiScaleHessianBasedMeasureImageFilter<ImageType, HessianImageType, ImageType>;
  auto multiScaleEnhancementFilter = MultiScaleEnhancementFilterType::New();
  multiScaleEnhancementFilter->SetInput(input);
  multiScaleEnhancementFilter->SetHessianToMeasureFilter(objectnessFilter);
  multiScaleEnhancementFilter->SetSigmaStepMethodToLogarithmic();
  multiScaleEnhancementFilter->SetSigmaMinimum(sigmaMinimum);
  multiScaleEnhancementFilter->SetSigmaMaximum(sigmaMaximum);
  multiScaleEnhancementFilter->SetNumberOfSigmaSteps(numberOfSigmaSteps);

  using OutputImageType = itk::Image<unsigned char, Dimension>;
  using RescaleFilterType = itk::RescaleIntensityImageFilter<ImageType, OutputImageType>;
  auto rescaleFilter = RescaleFilterType::New();
  rescaleFilter->SetInput(multiScaleEnhancementFilter->GetOutput());

  try
  {
    itk::WriteImage(rescaleFilter->GetOutput(), outputFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
