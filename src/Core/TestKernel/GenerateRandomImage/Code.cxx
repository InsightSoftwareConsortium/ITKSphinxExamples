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
#include "itkRandomImageSource.h"
#include "itkImageFileWriter.h"

int
main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage:" << std::endl;
    std::cerr << argv[0] << " <OutputFileName>" << std::endl;
    return EXIT_FAILURE;
  }
  const char * outputFileName = argv[1];

  constexpr unsigned int Dimension = 2;
  using PixelType = unsigned char;

  using ImageType = itk::Image<PixelType, Dimension>;

  ImageType::SizeType size;
  size.Fill(10);

  using RandomImageSourceType = itk::RandomImageSource<ImageType>;

  auto randomImageSource = RandomImageSourceType::New();
  randomImageSource->SetNumberOfWorkUnits(1); // to produce reproducible results
  randomImageSource->SetSize(size);

  try
  {
    itk::WriteImage(randomImageSource->GetOutput(), outputFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
