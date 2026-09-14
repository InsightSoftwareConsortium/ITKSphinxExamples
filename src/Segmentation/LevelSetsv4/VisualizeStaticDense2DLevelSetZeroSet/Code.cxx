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

#include "itkBinaryImageToLevelSetImageAdaptor.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkLevelSetDenseImage.h"
#include "itkOtsuMultipleThresholdsImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkZeroCrossingImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Missing Arguments" << std::endl;
    std::cerr << argv[0] << std::endl;
    std::cerr << "<Input Image> <Output Image>" << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  using InputPixelType = unsigned char;
  using InputImageType = itk::Image<InputPixelType, Dimension>;

  InputImageType::Pointer input = itk::ReadImage<InputImageType>(argv[1]);

  using LevelSetPixelType = float;
  using LevelSetImageType = itk::Image<LevelSetPixelType, Dimension>;
  using LevelSetType = itk::LevelSetDenseImage<LevelSetImageType>;

  // Generate a binary mask that will be used as initialization for the level
  // set.
  using OtsuFilterType = itk::OtsuMultipleThresholdsImageFilter<InputImageType, LevelSetImageType>;
  auto otsu = OtsuFilterType::New();
  otsu->SetInput(input);
  otsu->SetNumberOfHistogramBins(256);
  otsu->SetNumberOfThresholds(1);

  using RescaleType = itk::RescaleIntensityImageFilter<LevelSetImageType, LevelSetImageType>;
  auto rescaler = RescaleType::New();
  rescaler->SetInput(otsu->GetOutput());
  rescaler->SetOutputMinimum(0);
  rescaler->SetOutputMaximum(1);
  rescaler->Update();

  // Convert the binary mask to a level-set function
  using BinaryImageToLevelSetType = itk::BinaryImageToLevelSetImageAdaptor<LevelSetImageType, LevelSetType>;
  auto adaptor = BinaryImageToLevelSetType::New();
  adaptor->SetInputImage(rescaler->GetOutput());
  adaptor->Initialize();

  LevelSetType::Pointer levelSet = adaptor->GetModifiableLevelSet();

  using ZeroSetImageType = itk::Image<unsigned char, Dimension>;
  using ZeroCrossingFilterType = itk::ZeroCrossingImageFilter<LevelSetImageType, ZeroSetImageType>;
  auto zeroCrossing = ZeroCrossingFilterType::New();
  zeroCrossing->SetInput(levelSet->GetImage());
  zeroCrossing->SetForegroundValue(255);
  zeroCrossing->SetBackgroundValue(0);

  try
  {
    itk::WriteImage(zeroCrossing->GetOutput(), argv[2]);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
