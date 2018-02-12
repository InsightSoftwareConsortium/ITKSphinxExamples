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

#include "itkMemoryProbe.h"
#include <iostream>

int main( int argc, char* argv[] )
{
  if( argc != 2 )
    {
    std::cerr << "Usage:" << std::endl;
    std::cerr << argv[0] << " <Size of the array>" << std::endl;
    return EXIT_FAILURE;
    }

  const auto N = static_cast< unsigned int >( atoi( argv[1] ) );

  if( N == 0 )
    {
    std::cerr << "Size of the array should be non null" << std::endl;
    return EXIT_FAILURE;
    }

  itk::MemoryProbe memoryProbe;

  memoryProbe.Start();
  std::cout << "We are measuring " << memoryProbe.GetType();
  std::cout << " in units of " << memoryProbe.GetUnit() << ".\n" << std::endl;
  memoryProbe.Stop();

  // Expect zeros here
  std::cout << "** Start **" << std::endl;
  std::cout << "Mean: " << memoryProbe.GetMean() << std::endl;
  std::cout << "Total: " << memoryProbe.GetTotal() << std::endl;
  std::cout << std::endl;

  memoryProbe.Start();
  auto* a = new char[N];
  // The memory must be used for it to be counted.
  for(unsigned int i = 0; i < N; ++i)
    {
    a[i] = static_cast< char >( i*i );
    }
  memoryProbe.Stop();

  std::cout << "** After allocation **" << std::endl;
  std::cout << "Mean: " << memoryProbe.GetMean() << std::endl;
  std::cout << "Total: " << memoryProbe.GetTotal() << std::endl;
  std::cout << std::endl;

  memoryProbe.Start();
  delete[] a;
  memoryProbe.Stop();

  std::cout << "** After deallocation **" << std::endl;
  std::cout << "Mean: " << memoryProbe.GetMean() << std::endl;
  std::cout << "Total: " << memoryProbe.GetTotal() << std::endl;

  return EXIT_SUCCESS;
}
