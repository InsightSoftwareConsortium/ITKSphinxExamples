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

#include "itkNumericSeriesFileNames.h"

int
main()
{
  itk::NumericSeriesFileNames::Pointer numericSeriesFileNames = itk::NumericSeriesFileNames::New();
  numericSeriesFileNames->SetStartIndex(0);
  numericSeriesFileNames->SetEndIndex(150);
  numericSeriesFileNames->SetIncrementIndex(10);
  numericSeriesFileNames->SetSeriesFormat("output_%d.png");

  std::vector<std::string> fileNames = numericSeriesFileNames->GetFileNames();

  for (const auto & fileName : fileNames)
  {
    std::cout << fileName << std::endl;
  }

  std::cout << std::endl;
  std::cout << "***************" << std::endl;
  std::cout << std::endl;

  numericSeriesFileNames->SetSeriesFormat("output_%04d.png");

  fileNames = numericSeriesFileNames->GetFileNames();

  for (const auto & fileName : fileNames)
  {
    std::cout << fileName << std::endl;
  }

  return EXIT_SUCCESS;
}
