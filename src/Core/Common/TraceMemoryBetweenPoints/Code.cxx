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

  const unsigned int N = static_cast< unsigned int >( atoi( argv[1] ) );

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
  char* a = new char[N];
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
