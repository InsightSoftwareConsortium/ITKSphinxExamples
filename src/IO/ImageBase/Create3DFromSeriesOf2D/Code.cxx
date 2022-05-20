/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#include "itkImage.h"
#include "itkImageSeriesReader.h"
#include "itkImageFileWriter.h"
#include "itkNumericSeriesFileNames.h"

int
main(int argc, char * argv[])
{
  // Verify the number of parameters in the command line
  if (argc < 5)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " pattern firstSliceValue lastSliceValue outputImageFile" << std::endl;
    return EXIT_FAILURE;
  }

  using PixelType = unsigned char;
  constexpr unsigned int Dimension = 3;

  using ImageType = itk::Image<PixelType, Dimension>;
  using ReaderType = itk::ImageSeriesReader<ImageType>;

  auto reader = ReaderType::New();

  const unsigned int first = std::stoi(argv[2]);
  const unsigned int last = std::stoi(argv[3]);

  const char * outputFileName = argv[4];

  using NameGeneratorType = itk::NumericSeriesFileNames;

  auto nameGenerator = NameGeneratorType::New();

  nameGenerator->SetSeriesFormat(argv[1]);

  nameGenerator->SetStartIndex(first);
  nameGenerator->SetEndIndex(last);
  nameGenerator->SetIncrementIndex(1);
  std::vector<std::string> names = nameGenerator->GetFileNames();

  // List the files
  //
  std::vector<std::string>::iterator nit;
  for (nit = names.begin(); nit != names.end(); ++nit)
  {
    std::cout << "File: " << (*nit).c_str() << std::endl;
  }

  reader->SetFileNames(names);

  try
  {
    itk::WriteImage(reader->GetOutput(), outputFileName);
  }
  catch (const itk::ExceptionObject & err)
  {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
