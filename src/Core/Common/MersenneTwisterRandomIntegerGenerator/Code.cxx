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

#include "itkMersenneTwisterRandomVariateGenerator.h"

int
main()
{
  using GeneratorType = itk::Statistics::MersenneTwisterRandomVariateGenerator;
  GeneratorType::Pointer generator = GeneratorType::New();
  generator->Initialize();

  // Get an int between 0 and 5
  // (inclusive - that is sample from the set {0,1,2,3,4,5})
  std::cout << generator->GetIntegerVariate(5) << std::endl;

  return EXIT_SUCCESS;
}
