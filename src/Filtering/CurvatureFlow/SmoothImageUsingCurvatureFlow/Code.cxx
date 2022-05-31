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
#include "itkImage.h"
#include "itkCastImageFilter.h"
#include "itkCurvatureFlowImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itkImageFileReader.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage [iterations]" << std::endl;
    return EXIT_FAILURE;
  }

  int iterations = 5;
  if (argc > 2)
  {
    iterations = std::stoi(argv[2]);
  }

  using InternalPixelType = float;
  constexpr unsigned int Dimension = 2;
  using InternalImageType = itk::Image<InternalPixelType, Dimension>;

  const auto input = itk::ReadImage<InternalImageType>(argv[1]);

  using CurvatureFlowImageFilterType = itk::CurvatureFlowImageFilter<InternalImageType, InternalImageType>;

  auto smoothing = CurvatureFlowImageFilterType::New();

  smoothing->SetInput(input);
  smoothing->SetNumberOfIterations(iterations);
  smoothing->SetTimeStep(0.125);

  using SubtractImageFilterType = itk::SubtractImageFilter<InternalImageType>;
  auto diff = SubtractImageFilterType::New();
  diff->SetInput1(input);
  diff->SetInput2(smoothing->GetOutput());

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage<InternalImageType>(input, true, itksys::SystemTools::GetFilenameName(argv[1]));

  std::stringstream desc;
  desc << "CurvatureFlow\niterations = " << iterations;
  viewer.AddImage<InternalImageType>(smoothing->GetOutput(), true, desc.str());

  std::stringstream desc2;
  desc2 << "Original - CurvatureFlow";
  viewer.AddImage<InternalImageType>(diff->GetOutput(), true, desc2.str());

  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}
