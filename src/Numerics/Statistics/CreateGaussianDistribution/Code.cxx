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
#include "itkGaussianDistribution.h"

int
main(int, char *[])
{
  itk::Statistics::GaussianDistribution::Pointer gaussian = itk::Statistics::GaussianDistribution::New();
  gaussian->SetMean(2.0);
  gaussian->SetVariance(1.0);
  std::cout << gaussian->EvaluatePDF(2.1) << std::endl;
  return EXIT_SUCCESS;
}
