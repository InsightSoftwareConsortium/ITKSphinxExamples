/*=========================================================================
 *
 *  Copyright Insight Software Consortium
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
#include "itkImageFileReader.h"

int
main(int, char *[])
{
  constexpr unsigned int Dimension = 2;
  using PixelType = double;

  using ImageType = itk::Image<PixelType, Dimension>;
  using ReaderType = itk::ImageFileReader<ImageType>;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName("nofile.png");

  try
  {
    reader->Update();
  }
  catch (itk::ExceptionObject & err)
  {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;

    // Since the goal of the example is to catch the exception,
    // we declare this a success.
    return EXIT_SUCCESS;
  }

  // Since the goal of the example is to catch the exception,
  // the example fails if it is not caught.
  return EXIT_FAILURE;
}
