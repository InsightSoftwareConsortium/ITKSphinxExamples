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
#include "itkMedianImageFilter.h"
#include "itkPasteImageFilter.h"
#include "itkSubtractImageFilter.h"

#include "itksys/SystemTools.hxx"

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
    std::cerr << argv[0] << " InputImageFile [radius]" << std::endl;
    return EXIT_FAILURE;
  }
  std::string inputFileName = argv[1];

  // Setup types
  using ImageType = itk::Image<float, 2>;
  using FilterType = itk::MedianImageFilter<ImageType, ImageType>;
  using SubtractType = itk::SubtractImageFilter<ImageType>;
  using PasteType = itk::PasteImageFilter<ImageType, ImageType>;

  const auto input = itk::ReadImage<ImageType>(inputFileName);

  // Create and setup a median filter
  auto medianFilter = FilterType::New();
  auto radius = FilterType::InputSizeType::Filled(2);
  if (argc > 2)
  {
    radius.Fill(atoi(argv[2]));
  }

  itk::Size<2> processSize;
  processSize[0] = input->GetLargestPossibleRegion().GetSize()[0] / 2;
  processSize[1] = input->GetLargestPossibleRegion().GetSize()[1] / 2;

  itk::Index<2> processIndex;
  processIndex[0] = processSize[0] / 2;
  processIndex[1] = processSize[1] / 2;

  itk::ImageRegion<2> processRegion(processIndex, processSize);

  medianFilter->SetRadius(radius);
  medianFilter->SetInput(input);
  medianFilter->GetOutput()->SetRequestedRegion(processRegion);

  auto pasteFilter = PasteType::New();

  pasteFilter->SetSourceImage(medianFilter->GetOutput());
  pasteFilter->SetSourceRegion(medianFilter->GetOutput()->GetRequestedRegion());
  pasteFilter->SetDestinationImage(input);
  pasteFilter->SetDestinationIndex(processIndex);

  auto diff = SubtractType::New();
  diff->SetInput1(input);
  diff->SetInput2(pasteFilter->GetOutput());

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(input.GetPointer(), true, itksys::SystemTools::GetFilenameName(inputFileName));

  std::stringstream desc;
  desc << "Median/PasteImageFilter, radius = " << radius;
  viewer.AddImage(pasteFilter->GetOutput(), true, desc.str());

  std::stringstream desc2;
  desc2 << "Original - Median/Paste";
  viewer.AddImage(diff->GetOutput(), true, desc2.str());

  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}
