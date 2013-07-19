#include "itkMersenneTwisterRandomVariateGenerator.h"

int main(int, char*[])
{
  typedef itk::Statistics::MersenneTwisterRandomVariateGenerator GeneratorType;
  GeneratorType::Pointer generator = GeneratorType::New();
  generator->Initialize();

  // Get an int between 0 and 5
  // (inclusive - that is sample from the set {0,1,2,3,4,5})
  std::cout << generator->GetIntegerVariate(5) << std::endl;

  return EXIT_SUCCESS;
}
