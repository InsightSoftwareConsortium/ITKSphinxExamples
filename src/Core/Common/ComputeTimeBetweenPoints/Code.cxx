#include "itkTimeProbe.h"
#include "itkNumericTraits.h"

#include <iostream>
#include <string>

void LongFunction()
{
  for(int i = 0; i < itk::NumericTraits< int >::max() / 100; i++)
    {
    double a = 0;
    }
}

int main(int, char *[])
{
  itk::TimeProbe clock;

  clock.Start();
  LongFunction();

  clock.Stop();
  std::cout << "Mean: " << clock.GetMean() << std::endl;
  std::cout << "Total: " << clock.GetTotal() << std::endl;

  clock.Start();
  LongFunction();

  clock.Stop();
  std::cout << "Mean: " << clock.GetMean() << std::endl;
  std::cout << "Total: " << clock.GetTotal() << std::endl;

  return EXIT_SUCCESS;
}
