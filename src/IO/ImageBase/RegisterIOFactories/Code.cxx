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

#include "itkImageFileReader.h"
#include "itkMetaImageIOFactory.h"
#include "itkPNGImageIOFactory.h"

int
main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <MetaImageFileName> <PNGFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * metaImageFileName = argv[1];
  const char * pngFileName = argv[2];

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  using ReaderType = itk::ImageFileReader<ImageType>;
  ReaderType::Pointer reader = ReaderType::New();

  using RegisteredObjectsContainerType = std::list<itk::LightObject::Pointer>;


  RegisteredObjectsContainerType registeredIOs = itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");
  std::cout << "When CMake is not used to register the IO classes, there are\n"
            << registeredIOs.size() << " IO objects available to the ImageFileReader.\n"
            << std::endl;


  std::cout << "When we try to read a MetaImage, we will ";
  reader->SetFileName(metaImageFileName);
  try
  {
    reader->Update();
  }
  catch (itk::ImageFileReaderException &)
  {
    std::cout << "fail.\n" << std::endl;
    return EXIT_FAILURE;
  }


  std::cout << "After registering the MetaImageIO object, ";
  itk::MetaImageIOFactory::RegisterOneFactory();

  std::cout << "there are\n";
  registeredIOs = itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");
  std::cout << registeredIOs.size() << " IO objects available to the ImageFileReader.\n" << std::endl;

  std::cout << "Now, when we try to read a MetaImage, we will ";
  try
  {
    reader->Update();
    std::cout << "succeed.\n" << std::endl;
  }
  catch (itk::ImageFileReaderException & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }


  std::cout << "Every format desired to be supported by the reader\n"
            << "must be registered." << std::endl;
  itk::PNGImageIOFactory::RegisterOneFactory();
  reader->SetFileName(pngFileName);
  try
  {
    reader->Update();
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }


  return EXIT_SUCCESS;
}
