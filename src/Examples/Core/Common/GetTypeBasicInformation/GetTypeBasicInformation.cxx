#include "itkNumericTraits.h"

int main(int, char* [] )
{
  typedef float MyType;

  std::cout << "Min: " << itk::NumericTraits< MyType >::min() << std::endl;
  std::cout << "Max: " << itk::NumericTraits< MyType >::max() << std::endl;
  std::cout << "Zero: " << itk::NumericTraits< MyType >::Zero << std::endl;
  std::cout << "ZeroValue: " << itk::NumericTraits< MyType >::ZeroValue()
            << std::endl;

  std::cout << "Is -1 negative? "
            << itk::NumericTraits< MyType >::IsNegative(-1) << std::endl;

  std::cout << "Is 1 negative? "
            << itk::NumericTraits< MyType >::IsNegative(1)
            << std::endl;

  std::cout << "One: "
            << itk::NumericTraits< MyType >::One
            << std::endl;

  std::cout << "Epsilon: "
            << itk::NumericTraits< MyType >::epsilon()
            << std::endl;

  std::cout << "Infinity: "
            << itk::NumericTraits< MyType >::infinity() << std::endl;

  if(0 == itk::NumericTraits< MyType >::infinity())
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
