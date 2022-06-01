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
#include "itkImageAdaptor.h"
#include "itkImageRegionIterator.h"
#include "itkNthElementImageAdaptor.h"
#include "itkMinMaxCurvatureFlowImageFilter.h"
#include "itkComposeImageFilter.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkRGBPixel.h"

#include <sstream>

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

int
main(int argc, char * argv[])
{
  // Verify command line arguments
  if (argc < 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " InputImageFile [iterations]" << std::endl;
    return EXIT_FAILURE;
  }

  int iterations = 5;
  if (argc > 2)
  {
    std::stringstream ss(argv[2]);
    ss >> iterations;
  }
  std::string inputFileName = argv[1];

  // Setup types
  using ComponentType = float;
  using PixelType = itk::RGBPixel<ComponentType>;
  using RGBImageType = itk::Image<PixelType, 2>;
  using ImageType = itk::Image<ComponentType, 2>;
  using ImageAdaptorType = itk::NthElementImageAdaptor<RGBImageType, unsigned char>;
  using ComposeType = itk::ComposeImageFilter<ImageType, RGBImageType>;
  using CurvatureFlowType = itk::MinMaxCurvatureFlowImageFilter<ImageAdaptorType, ImageType>;

  const auto input = itk::ReadImage<RGBImageType>(inputFileName);

  // Run the filter for each component
  auto rAdaptor = ImageAdaptorType::New();
  rAdaptor->SelectNthElement(0);
  rAdaptor->SetImage(input);

  auto rCurvatureFilter = CurvatureFlowType::New();
  rCurvatureFilter->SetInput(rAdaptor);
  rCurvatureFilter->SetNumberOfIterations(iterations);
  rCurvatureFilter->Update();

  auto gAdaptor = ImageAdaptorType::New();
  gAdaptor->SelectNthElement(1);
  gAdaptor->SetImage(input);

  auto gCurvatureFilter = CurvatureFlowType::New();
  gCurvatureFilter->SetInput(gAdaptor);
  gCurvatureFilter->SetNumberOfIterations(iterations);
  gCurvatureFilter->Update();

  auto bAdaptor = ImageAdaptorType::New();
  bAdaptor->SelectNthElement(2);
  bAdaptor->SetImage(input);

  auto bCurvatureFilter = CurvatureFlowType::New();
  bCurvatureFilter->SetInput(bAdaptor);
  bCurvatureFilter->SetNumberOfIterations(iterations);
  bCurvatureFilter->Update();

  // compose an RGB image from the three filtered images

  auto compose = ComposeType::New();
  compose->SetInput1(rCurvatureFilter->GetOutput());
  compose->SetInput2(gCurvatureFilter->GetOutput());
  compose->SetInput3(bCurvatureFilter->GetOutput());

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddRGBImage(input.GetPointer(), true, itksys::SystemTools::GetFilenameName(inputFileName));

  std::stringstream desc;
  desc << "MinMaxCurvatureFlow iterations = " << iterations;
  viewer.AddRGBImage(compose->GetOutput(), true, desc.str());

  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}
