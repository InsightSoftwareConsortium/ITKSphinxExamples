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
#include "itkBilateralImageFilter.h"
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
    std::cerr << argv[0] << " inputImageFile [domainSigma] [rangeSigma]" << std::endl;
    return EXIT_FAILURE;
  }
  double rangeSigma = 2.0;
  double domainSigma = 2.0;
  if (argc > 2)
  {
    domainSigma = std::stod(argv[2]);
  }
  if (argc > 3)
  {
    rangeSigma = std::stod(argv[3]);
  }

  // Parse command line arguments
  std::string inputFileName = argv[1];

  // Setup types
  using ImageType = itk::Image<float, 2>;
  using FilterType = itk::BilateralImageFilter<ImageType, ImageType>;
  using SubtractImageFilterType = itk::SubtractImageFilter<ImageType>;

  const auto input = itk::ReadImage<ImageType>(inputFileName);

  // Create and setup a derivative filter
  FilterType::Pointer bilateralFilter = FilterType::New();
  bilateralFilter->SetInput(input);
  bilateralFilter->SetDomainSigma(domainSigma);
  bilateralFilter->SetRangeSigma(rangeSigma);

  SubtractImageFilterType::Pointer diff = SubtractImageFilterType::New();
  diff->SetInput1(input);
  diff->SetInput2(bilateralFilter->GetOutput());

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(input, true, itksys::SystemTools::GetFilenameName(argv[1]));

  std::stringstream desc;
  desc << "Bilateral\ndomainSigma = " << domainSigma << " rangeSigma = " << rangeSigma;
  viewer.AddImage(bilateralFilter->GetOutput(), true, desc.str());

  std::stringstream desc2;
  desc2 << "Original - Bilateral";
  viewer.AddImage(diff->GetOutput(), true, desc2.str());

  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}
