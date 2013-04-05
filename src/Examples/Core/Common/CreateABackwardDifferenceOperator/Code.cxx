#include <itkBackwardDifferenceOperator.h>

int main(int, char*[])
{
  typedef float PixelType;
  const unsigned int Dimension = 2;

  typedef itk::BackwardDifferenceOperator< PixelType, Dimension >
    BackwardDifferenceOperatorType;
  BackwardDifferenceOperatorType backwardDifferenceOperator;

  // Create the operator for the X axis derivative
  backwardDifferenceOperator.SetDirection(0);

  itk::Size< Dimension > radius;
  radius.Fill(1);

  backwardDifferenceOperator.CreateToRadius(radius);

  std::cout << "Size: " << backwardDifferenceOperator.GetSize()
            << std::endl;

  std::cout << backwardDifferenceOperator << std::endl;

  for(unsigned int i = 0; i < 9; i++)
    {
    std::cout << backwardDifferenceOperator.GetOffset(i) << " "
              << backwardDifferenceOperator.GetElement(i) << std::endl;
    }
  return EXIT_SUCCESS;
}
