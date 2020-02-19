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
  std::string inputFilename = argv[1];

  // Setup types
  using ImageType = itk::Image<float, 2>;
  using ReaderType = itk::ImageFileReader<ImageType>;
  using FilterType = itk::MedianImageFilter<ImageType, ImageType>;
  using SubtractType = itk::SubtractImageFilter<ImageType>;
  using PasteType = itk::PasteImageFilter<ImageType, ImageType>;

  // Create and setup a reader
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(inputFilename);

  // Create and setup a median filter
  FilterType::Pointer       medianFilter = FilterType::New();
  FilterType::InputSizeType radius;
  radius.Fill(2);
  if (argc > 2)
  {
    radius.Fill(atoi(argv[2]));
  }

  reader->Update();

  itk::Size<2> processSize;
  processSize[0] = reader->GetOutput()->GetLargestPossibleRegion().GetSize()[0] / 2;
  processSize[1] = reader->GetOutput()->GetLargestPossibleRegion().GetSize()[1] / 2;

  itk::Index<2> processIndex;
  processIndex[0] = processSize[0] / 2;
  processIndex[1] = processSize[1] / 2;

  itk::ImageRegion<2> processRegion(processIndex, processSize);

  medianFilter->SetRadius(radius);
  medianFilter->SetInput(reader->GetOutput());
  medianFilter->GetOutput()->SetRequestedRegion(processRegion);

  PasteType::Pointer pasteFilter = PasteType::New();

  pasteFilter->SetSourceImage(medianFilter->GetOutput());
  pasteFilter->SetSourceRegion(medianFilter->GetOutput()->GetRequestedRegion());
  pasteFilter->SetDestinationImage(reader->GetOutput());
  pasteFilter->SetDestinationIndex(processIndex);

  SubtractType::Pointer diff = SubtractType::New();
  diff->SetInput1(reader->GetOutput());
  diff->SetInput2(pasteFilter->GetOutput());

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(reader->GetOutput(), true, itksys::SystemTools::GetFilenameName(inputFilename));

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
