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

#include "itkImageSeriesReader.h"
#include "itkNumericSeriesFileNames.h"

int
main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <seriesFormat> <startIndex> <endIndex>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * seriesFormat = argv[1];
  unsigned int startIndex = std::stoi(argv[2]);
  unsigned int endIndex = std::stoi(argv[3]);

  constexpr unsigned int Dimension = 3;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  using NameGeneratorType = itk::NumericSeriesFileNames;
  NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();
  nameGenerator->SetSeriesFormat(seriesFormat);
  nameGenerator->SetStartIndex(startIndex);
  nameGenerator->SetEndIndex(endIndex);
  std::vector<std::string> fileNames = nameGenerator->GetFileNames();

  using ReaderType = itk::ImageSeriesReader<ImageType>;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileNames(fileNames);

  try
  {
    reader->Update();

    ImageType::ConstPointer     output = reader->GetOutput();
    const ImageType::RegionType largestRegion = output->GetLargestPossibleRegion();
    std::cout << "Initial LargestPossibleRegion: ";
    std::cout << largestRegion << std::endl;
    ;
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  fileNames.pop_back();

  try
  {
    std::cout << "\nTrying to call Update() "
              << "after shrinking the LargestPossibleRegion...\n"
              << std::endl;
    reader->SetFileNames(fileNames);
    reader->Update();
  }
  catch (itk::ExceptionObject & error)
  {
    // Print out the error that occurs
    std::cout << "Error: " << error << std::endl;
  }

  try
  {
    std::cout << "Trying to call UpdateLargestPossibleRegion() "
              << "after shrinking the LargestPossibleRegion...\n"
              << std::endl;
    reader->SetFileNames(fileNames);
    reader->UpdateLargestPossibleRegion();

    ImageType::ConstPointer     output = reader->GetOutput();
    const ImageType::RegionType largestRegion = output->GetLargestPossibleRegion();
    std::cout << "Shrunk LargestPossibleRegion: ";
    std::cout << largestRegion << std::endl;
    ;
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
