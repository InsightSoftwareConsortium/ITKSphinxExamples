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

#include "itkPointSet.h"

int
main(int argc, char * argv[])
{
  // Verify the number of parameters in the command line
  if (argc < 1)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " outputFile " << std::endl;
    return EXIT_FAILURE;
  }

  std::string outputFilename = argv[1];

  // Store points
  typedef itk::PointSet<double, 3> PointSetType;
  PointSetType::Pointer            pointsSet = PointSetType::New();
  typedef PointSetType::PointType  PointType;


  return EXIT_SUCCESS;
}
