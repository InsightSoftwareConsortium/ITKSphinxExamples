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
#include "itkRescaleIntensityImageFilter.h"
#include "itkBinomialBlurImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc < 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputImageFile  outputImageFile  numberOfRepetitions" << std::endl;
    return EXIT_FAILURE;
  }

  using InputPixelType = float;
  using OutputPixelType = float;
  using InputImageType = itk::Image<InputPixelType, 2>;
  using OutputImageType = itk::Image<OutputPixelType, 2>;

  const auto input = itk::ReadImage<InputImageType>(argv[1]);

  const unsigned int repetitions = std::stoi(argv[3]);

  using FilterType = itk::BinomialBlurImageFilter<InputImageType, OutputImageType>;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(input);
  filter->SetRepetitions(repetitions);
  filter->Update();

  using WritePixelType = unsigned char;
  using WriteImageType = itk::Image<WritePixelType, 2>;
  using RescaleFilterType = itk::RescaleIntensityImageFilter<OutputImageType, WriteImageType>;

  RescaleFilterType::Pointer rescaler = RescaleFilterType::New();
  rescaler->SetOutputMinimum(0);
  rescaler->SetOutputMaximum(255);
  rescaler->SetInput(filter->GetOutput());

  itk::WriteImage(rescaler->GetOutput(), argv[2]);

  return EXIT_SUCCESS;
}
