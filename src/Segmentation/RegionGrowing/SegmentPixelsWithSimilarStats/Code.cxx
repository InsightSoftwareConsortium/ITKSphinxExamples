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
#include "itkConfidenceConnectedImageFilter.h"

#include "itksys/SystemTools.hxx"
#include <sstream>

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

using ImageType = itk::Image<unsigned char, 2>;

int
main(int argc, char * argv[])
{
  if (argc < 4)
  {
    std::cerr << "Required: filename.png seedX seedY" << std::endl;

    return EXIT_FAILURE;
  }
  std::string inputFileName = argv[1];

  const auto input = itk::ReadImage<ImageType>(inputFileName);

  using ConfidenceConnectedFilterType = itk::ConfidenceConnectedImageFilter<ImageType, ImageType>;
  auto confidenceConnectedFilter = ConfidenceConnectedFilterType::New();
  confidenceConnectedFilter->SetInitialNeighborhoodRadius(3);
  confidenceConnectedFilter->SetMultiplier(3);
  confidenceConnectedFilter->SetNumberOfIterations(25);
  confidenceConnectedFilter->SetReplaceValue(255);

  // Set seed
  ImageType::IndexType seed;
  seed[0] = std::stoi(argv[2]);
  seed[1] = std::stoi(argv[3]);
  confidenceConnectedFilter->SetSeed(seed);
  confidenceConnectedFilter->SetInput(input);

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(input.GetPointer(), true, itksys::SystemTools::GetFilenameName(inputFileName));

  std::stringstream desc;
  desc << "ConfidenceConnected Seed: " << seed[0] << ", " << seed[1];
  viewer.AddImage(confidenceConnectedFilter->GetOutput(), true, desc.str());

  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}
