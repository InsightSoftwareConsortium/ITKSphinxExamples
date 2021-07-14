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
#include "itkBinaryMinMaxCurvatureFlowImageFilter.h"
#include "itkSubtractImageFilter.h"

#include "itksys/SystemTools.hxx"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << argv[0] << " InputFileName [NumberOfIterations]" << std ::endl;
    return EXIT_FAILURE;
  }

  std::string inputFileName = argv[1];

  unsigned int numberOfIterations = 2;
  if (argc > 2)
  {
    numberOfIterations = std::stoi(argv[2]);
  }

  constexpr unsigned int Dimension = 2;

  using InputPixelType = float;
  using OutputPixelType = float;
  using InputImageType = itk::Image<InputPixelType, Dimension>;
  using OutputImageType = itk::Image<OutputPixelType, Dimension>;

  const auto input = itk::ReadImage<InputImageType>(inputFileName);

  using FilterType = itk::BinaryMinMaxCurvatureFlowImageFilter<InputImageType, OutputImageType>;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(input);
  filter->SetThreshold(255);
  filter->SetNumberOfIterations(numberOfIterations);

  using SubtractType = itk::SubtractImageFilter<OutputImageType>;
  SubtractType::Pointer diff = SubtractType::New();
  diff->SetInput1(input);
  diff->SetInput2(filter->GetOutput());

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(input, true, itksys::SystemTools::GetFilenameName(inputFileName));

  std::stringstream desc;
  desc << "BinaryMinMaxCurvature, iterations = " << numberOfIterations;
  viewer.AddImage(filter->GetOutput(), true, desc.str());

  std::stringstream desc2;
  desc2 << "Original - BinaryMinMaxCurvatureFlow";
  viewer.AddImage(diff->GetOutput(), true, desc2.str());

  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}
