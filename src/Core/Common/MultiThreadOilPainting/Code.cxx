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

#include "itkOilPaintingImageFilter.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " inputFile [bins [radius]]" << std::endl;
    return EXIT_FAILURE;
  }
  unsigned int numberOfBins = 50;
  if (argc >= 3)
  {
    numberOfBins = std::stoi(argv[2]);
  }

  unsigned int radius = 2;
  if (argc >= 4)
  {
    radius = std::stoi(argv[3]);
  }

  using ImageType = itk::Image<unsigned char, 2>;
  using FilterType = itk::OilPaintingImageFilter<ImageType>;

  std::string inputFileName = argv[1];
  const auto  input = itk::ReadImage<ImageType>(inputFileName);

  auto filter = FilterType::New();
  filter->SetInput(input);
  filter->SetNumberOfBins(numberOfBins);
  filter->SetRadius(radius);
  filter->Update();

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(input.GetPointer(), true, itksys::SystemTools::GetFilenameName(inputFileName));

  std::stringstream desc;
  desc << "OilPaintingImageFilter, bins = " << numberOfBins << " radius = " << radius;
  viewer.AddImage(filter->GetOutput(), true, desc.str());

  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}
