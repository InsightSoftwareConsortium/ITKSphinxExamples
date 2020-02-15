/*=========================================================================
 *
 *  Copyright Insight Software Consortium
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
#include "itkMultiThreaderBase.h"
#include "itkMedianImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <NumberOfThreads>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const auto numberOfThreads = static_cast<unsigned int>(std::atoi(argv[1]));

  itk::MultiThreaderBase::SetGlobalDefaultNumberOfThreads(numberOfThreads);

  constexpr unsigned int Dimension = 2;
  using PixelType = float;
  using ImageType = itk::Image<PixelType, Dimension>;
  using FilterType = itk::MedianImageFilter<ImageType, ImageType>;
  FilterType::Pointer filter = FilterType::New();

  const auto filterDefaultThreads = filter->GetMultiThreader()->GetGlobalDefaultNumberOfThreads();
  std::cout << "Filter's default number of threads: " << filterDefaultThreads << std::endl;

  if (filterDefaultThreads != numberOfThreads)
  {
    std::cerr << "Filter does not have expected default number of threads." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
