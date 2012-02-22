#include "itkMersenneTwisterRandomVariateGenerator.h"

int main(int, char*[])
{
  typedef itk::Statistics::MersenneTwisterRandomVariateGenerator GeneratorType;
  GeneratorType::Pointer generator = GeneratorType::New();

  generator->Initialize();

  std::cout << generator->GetUniformVariate(0, 5) << std::endl;

  return EXIT_SUCCESS;
}
