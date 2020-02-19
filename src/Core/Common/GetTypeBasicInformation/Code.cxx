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

#include "itkNumericTraits.h"

int
main(int, char *[])
{
  using MyType = float;

  std::cout << "Min: " << itk::NumericTraits<MyType>::min() << std::endl;
  std::cout << "Max: " << itk::NumericTraits<MyType>::max() << std::endl;
  std::cout << "Zero: " << itk::NumericTraits<MyType>::Zero << std::endl;
  std::cout << "ZeroValue: " << itk::NumericTraits<MyType>::ZeroValue() << std::endl;

  std::cout << "Is -1 negative? " << itk::NumericTraits<MyType>::IsNegative(-1) << std::endl;

  std::cout << "Is 1 negative? " << itk::NumericTraits<MyType>::IsNegative(1) << std::endl;

  std::cout << "One: " << itk::NumericTraits<MyType>::One << std::endl;

  std::cout << "Epsilon: " << itk::NumericTraits<MyType>::epsilon() << std::endl;

  std::cout << "Infinity: " << itk::NumericTraits<MyType>::infinity() << std::endl;

  if (0 == itk::NumericTraits<MyType>::infinity())
  {
    std::cout << " 0 == inf!" << std::endl;
    return EXIT_FAILURE;
  }
  else
  {
    std::cout << "Good" << std::endl;
    return EXIT_SUCCESS;
  }
}
