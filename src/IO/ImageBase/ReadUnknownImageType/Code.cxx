/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkImageFileReader.h"
#include "itkImageIOBase.h"

template <class TImage>
int
ReadImage(const char * fileName, typename TImage::Pointer image)
{
  using ImageType = TImage;
  using ImageReaderType = itk::ImageFileReader<ImageType>;

  auto reader = ImageReaderType::New();
  reader->SetFileName(fileName);

  try
  {
    reader->Update();
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  image->Graft(reader->GetOutput());

  return EXIT_SUCCESS;
}

template <unsigned int VDimension>
int
ReadScalarImage(const char * inputFileName, const itk::IOComponentEnum componentType)
{
  switch (componentType)
  {
    default:
    case itk::IOComponentEnum::UNKNOWNCOMPONENTTYPE:
      std::cerr << "Unknown and unsupported component type!" << std::endl;
      return EXIT_FAILURE;

    case itk::IOComponentEnum::UCHAR:
    {
      using PixelType = unsigned char;
      using ImageType = itk::Image<PixelType, VDimension>;

      auto image = ImageType::New();

      if (ReadImage<ImageType>(inputFileName, image) == EXIT_FAILURE)
      {
        return EXIT_FAILURE;
      }

      std::cout << image << std::endl;
      break;
    }

    case itk::IOComponentEnum::CHAR:
    {
      using PixelType = char;
      using ImageType = itk::Image<PixelType, VDimension>;

      auto image = ImageType::New();

      if (ReadImage<ImageType>(inputFileName, image) == EXIT_FAILURE)
      {
        return EXIT_FAILURE;
      }

      std::cout << image << std::endl;
      break;
    }

    case itk::IOComponentEnum::USHORT:
    {
      using PixelType = unsigned short;
      using ImageType = itk::Image<PixelType, VDimension>;

      auto image = ImageType::New();

      if (ReadImage<ImageType>(inputFileName, image) == EXIT_FAILURE)
      {
        return EXIT_FAILURE;
      }

      std::cout << image << std::endl;
      break;
    }

    case itk::IOComponentEnum::SHORT:
    {
      using PixelType = short;
      using ImageType = itk::Image<PixelType, VDimension>;

      auto image = ImageType::New();

      if (ReadImage<ImageType>(inputFileName, image) == EXIT_FAILURE)
      {
        return EXIT_FAILURE;
      }

      std::cout << image << std::endl;
      break;
    }

    case itk::IOComponentEnum::UINT:
    {
      using PixelType = unsigned int;
      using ImageType = itk::Image<PixelType, VDimension>;

      auto image = ImageType::New();

      if (ReadImage<ImageType>(inputFileName, image) == EXIT_FAILURE)
      {
        return EXIT_FAILURE;
      }

      std::cout << image << std::endl;
      break;
    }

    case itk::IOComponentEnum::INT:
    {
      using PixelType = int;
      using ImageType = itk::Image<PixelType, VDimension>;

      auto image = ImageType::New();

      if (ReadImage<ImageType>(inputFileName, image) == EXIT_FAILURE)
      {
        return EXIT_FAILURE;
      }

      std::cout << image << std::endl;
      break;
    }

    case itk::IOComponentEnum::ULONG:
    {
      using PixelType = unsigned long;
      using ImageType = itk::Image<PixelType, VDimension>;

      auto image = ImageType::New();

      if (ReadImage<ImageType>(inputFileName, image) == EXIT_FAILURE)
      {
        return EXIT_FAILURE;
      }

      std::cout << image << std::endl;
      break;
    }

    case itk::IOComponentEnum::LONG:
    {
      using PixelType = long;
      using ImageType = itk::Image<PixelType, VDimension>;

      auto image = ImageType::New();

      if (ReadImage<ImageType>(inputFileName, image) == EXIT_FAILURE)
      {
        return EXIT_FAILURE;
      }

      std::cout << image << std::endl;
      break;
    }

    case itk::IOComponentEnum::FLOAT:
    {
      using PixelType = float;
      using ImageType = itk::Image<PixelType, VDimension>;

      auto image = ImageType::New();

      if (ReadImage<ImageType>(inputFileName, image) == EXIT_FAILURE)
      {
        return EXIT_FAILURE;
      }

      std::cout << image << std::endl;
      break;
    }

    case itk::IOComponentEnum::DOUBLE:
    {
      using PixelType = double;
      using ImageType = itk::Image<PixelType, VDimension>;

      auto image = ImageType::New();

      if (ReadImage<ImageType>(inputFileName, image) == EXIT_FAILURE)
      {
        return EXIT_FAILURE;
      }

      std::cout << image << std::endl;
      break;
    }
  }
  return EXIT_SUCCESS;
}

int
main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];

  itk::ImageIOBase::Pointer imageIO =
    itk::ImageIOFactory::CreateImageIO(inputFileName, itk::CommonEnums::IOFileMode::ReadMode);

  imageIO->SetFileName(inputFileName);
  imageIO->ReadImageInformation();

  using IOPixelType = itk::IOPixelEnum;
  const IOPixelType pixelType = imageIO->GetPixelType();

  std::cout << "Pixel Type is " << itk::ImageIOBase::GetPixelTypeAsString(pixelType) << std::endl;

  using IOComponentType = itk::IOComponentEnum;
  const IOComponentType componentType = imageIO->GetComponentType();

  std::cout << "Component Type is " << imageIO->GetComponentTypeAsString(componentType) << std::endl;

  const unsigned int imageDimension = imageIO->GetNumberOfDimensions();

  std::cout << "Image Dimension is " << imageDimension << std::endl;

  switch (pixelType)
  {
    case itk::IOPixelEnum::SCALAR:
    {
      if (imageDimension == 2)
      {
        return ReadScalarImage<2>(inputFileName, componentType);
      }
      else if (imageDimension == 3)
      {
        return ReadScalarImage<3>(inputFileName, componentType);
      }
      else if (imageDimension == 4)
      {
        return ReadScalarImage<4>(inputFileName, componentType);
      }
    }

    default:
      std::cerr << "not implemented yet!" << std::endl;
      return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
