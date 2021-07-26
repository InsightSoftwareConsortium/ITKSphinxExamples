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

#include "itkVTKVisualize2DSparseLevelSetLayers.h"

#include "itkBinaryImageToLevelSetImageAdaptor.h"
#include "itkImageFileReader.h"
#include "itkMalcolmSparseLevelSetImage.h"

#include "itkOtsuMultipleThresholdsImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "vtkRenderWindowInteractor.h"

int
main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Missing Arguments" << std::endl;
    std::cerr << argv[0] << std::endl;
    std::cerr << "<Input Image> <Interactive (0 or 1)>" << std::endl;
    return EXIT_FAILURE;
  }

  // Image Dimension
  constexpr unsigned int Dimension = 2;

  using InputPixelType = unsigned char;
  using InputImageType = itk::Image<InputPixelType, Dimension>;

  InputImageType::Pointer input = itk::ReadImage<InputImageType>(argv[1]);

  using LevelSetType = itk::MalcolmSparseLevelSetImage<Dimension>;

  // Generate a binary mask that will be used as initialization for the level
  // set evolution.
  using OtsuFilterType = itk::OtsuMultipleThresholdsImageFilter<InputImageType, InputImageType>;
  OtsuFilterType::Pointer otsu = OtsuFilterType::New();
  otsu->SetInput(input);
  otsu->SetNumberOfHistogramBins(256);
  otsu->SetNumberOfThresholds(1);

  using RescaleType = itk::RescaleIntensityImageFilter<InputImageType, InputImageType>;
  RescaleType::Pointer rescaler = RescaleType::New();
  rescaler->SetInput(otsu->GetOutput());
  rescaler->SetOutputMinimum(0);
  rescaler->SetOutputMaximum(1);

  // convert a binary mask to a level-set function
  using BinaryImageToLevelSetType = itk::BinaryImageToLevelSetImageAdaptor<InputImageType, LevelSetType>;

  BinaryImageToLevelSetType::Pointer adaptor = BinaryImageToLevelSetType::New();
  adaptor->SetInputImage(rescaler->GetOutput());
  adaptor->Initialize();

  LevelSetType::Pointer levelSet = adaptor->GetModifiableLevelSet();

  // Create the visualizer
  using VisualizationType = itk::VTKVisualize2DSparseLevelSetLayers<InputImageType, LevelSetType>;
  VisualizationType::Pointer visualizer = VisualizationType::New();
  visualizer->SetInputImage(input);
  visualizer->SetLevelSet(levelSet);
  visualizer->SetScreenCapture(true);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(visualizer->GetRenderWindow());

  try
  {
    visualizer->Update();
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  bool interactive = (std::stoi(argv[2]) != 0);
  if (interactive)
  {
    renderWindowInteractor->Start();
  }

  return EXIT_SUCCESS;
}
