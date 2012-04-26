#include "itkNumericSeriesFileNames.h"

int main(int, char *[])
{
  itk::NumericSeriesFileNames::Pointer numericSeriesFileNames =
    itk::NumericSeriesFileNames::New();
  numericSeriesFileNames->SetStartIndex(0);
  numericSeriesFileNames->SetEndIndex(150);
  numericSeriesFileNames->SetIncrementIndex(10);
  numericSeriesFileNames->SetSeriesFormat("output_%d.png");

  std::vector< std::string > fileNames =
    numericSeriesFileNames->GetFileNames();

  for(size_t i = 0; i < fileNames.size(); ++i)
    {
    std::cout << fileNames[i] << std::endl;
    }

  std::cout << std::endl;
  std::cout << "***************" << std::endl;
  std::cout << std::endl;

  numericSeriesFileNames->SetSeriesFormat("output_%04d.png");

  fileNames = numericSeriesFileNames->GetFileNames();

  for(size_t i = 0; i < fileNames.size(); ++i)
    {
    std::cout << fileNames[i] << std::endl;
    }

  return EXIT_SUCCESS;
}
