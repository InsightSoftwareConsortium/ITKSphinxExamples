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

#include "itkTimeProbe.h"
#include "itkNumericTraits.h"

#include <iostream>
#include <string>

void
LongFunction()
{
  for (int i = 0; i < itk::NumericTraits<int>::max() / 100; ++i)
  {
    double a = 0;
    (void)a;
  }
}

int
main()
{
  itk::TimeProbe clock;

  clock.Start();
  LongFunction();

  clock.Stop();
  std::cout << "Mean: " << clock.GetMean() << std::endl;
  std::cout << "Total: " << clock.GetTotal() << std::endl;

  clock.Start();
  LongFunction();

  clock.Stop();
  std::cout << "Mean: " << clock.GetMean() << std::endl;
  std::cout << "Total: " << clock.GetTotal() << std::endl;

  clock.Report();

  return EXIT_SUCCESS;
}
