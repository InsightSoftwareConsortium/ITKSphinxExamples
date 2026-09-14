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
#include "itkImageRegionIteratorWithIndex.h"
#include "itkShiSparseLevelSetImage.h"
#include "itkOtsuMultipleThresholdsImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

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

  using LevelSetType = itk::ShiSparseLevelSetImage<Dimension>;

  // Generate a binary mask that will be used as initialization for the level
  // set.
  using OtsuFilterType = itk::OtsuMultipleThresholdsImageFilter<InputImageType, InputImageType>;
  auto otsu = OtsuFilterType::New();
  otsu->SetInput(input);
  otsu->SetNumberOfHistogramBins(256);
  otsu->SetNumberOfThresholds(1);

  using RescaleType = itk::RescaleIntensityImageFilter<InputImageType, InputImageType>;
  auto rescaler = RescaleType::New();
  rescaler->SetInput(otsu->GetOutput());
  rescaler->SetOutputMinimum(0);
  rescaler->SetOutputMaximum(1);
  rescaler->Update();

  // Convert the binary mask to a sparse level-set function
  using BinaryImageToLevelSetType = itk::BinaryImageToLevelSetImageAdaptor<InputImageType, LevelSetType>;
  auto adaptor = BinaryImageToLevelSetType::New();
  adaptor->SetInputImage(rescaler->GetOutput());
  adaptor->Initialize();

  LevelSetType::Pointer levelSet = adaptor->GetModifiableLevelSet();

  // Sample the level-set function on the image grid to show its layers
  using LayerImageType = itk::Image<LevelSetType::OutputType, Dimension>;
  auto layers = LayerImageType::New();
  layers->CopyInformation(input);
  layers->SetRegions(input->GetLargestPossibleRegion());
  layers->Allocate();

  itk::ImageRegionIteratorWithIndex<LayerImageType> it(layers, layers->GetLargestPossibleRegion());
  for (it.GoToBegin(); !it.IsAtEnd(); ++it)
  {
    it.Set(levelSet->Evaluate(it.GetIndex()));
  }

  try
  {
    itk::WriteImage(layers, argv[2]);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
