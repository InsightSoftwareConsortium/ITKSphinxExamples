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
#include "itkImageFileReader.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkLaplacianSharpeningImageFilter.h"
#include "itkSubtractImageFilter.h"

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
    std::cerr << argv[0] << " inputImageFile" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse command line arguments
  std::string inputFileName = argv[1];

  // Setup types
  using FloatImageType = itk::Image<float, 2>;

  const auto input = itk::ReadImage<FloatImageType>(inputFileName);

  using LaplacianSharpeningImageFilterType = itk::LaplacianSharpeningImageFilter<FloatImageType, FloatImageType>;
  LaplacianSharpeningImageFilterType::Pointer laplacianSharpeningImageFilter =
    LaplacianSharpeningImageFilterType::New();
  laplacianSharpeningImageFilter->SetInput(input);

  using SubtractType = itk::SubtractImageFilter<FloatImageType>;
  auto diff = SubtractType::New();
  diff->SetInput1(input);
  diff->SetInput2(laplacianSharpeningImageFilter->GetOutput());

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(input.GetPointer(), true, itksys::SystemTools::GetFilenameName(argv[1]));

  std::stringstream desc;
  desc << "LaplacianSharpeningImageFilter";
  viewer.AddImage(laplacianSharpeningImageFilter->GetOutput(), true, desc.str());

  std::stringstream desc2;
  desc2 << "Original - LaplacianSharpening";
  viewer.AddImage(diff->GetOutput(), true, desc2.str());

  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}
