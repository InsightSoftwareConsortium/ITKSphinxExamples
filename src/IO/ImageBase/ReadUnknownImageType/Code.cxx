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
#include "itkImageFileWriter.h"
#include "itkImageIOBase.h"

template< class TImage >
int ReadImage( const char* fileName,
               typename TImage::Pointer image )
{
  typedef TImage                            ImageType;
  typedef itk::ImageFileReader< ImageType > ImageReaderType;

  typename ImageReaderType::Pointer reader = ImageReaderType::New();
  reader->SetFileName( fileName );

  try
    {
    reader->Update();
    }
  catch( itk::ExceptionObject& e )
    {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
    }

  image->Graft( reader->GetOutput() );

  return EXIT_SUCCESS;
}

template< unsigned int VDimension >
int ReadScalarImage( const char* inputFileName,
                     const itk::ImageIOBase::IOComponentType componentType )
{
  switch( componentType )
    {
    default:
    case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
      std::cerr << "Unknown and unsupported component type!" << std::endl;
      return EXIT_FAILURE;

    case itk::ImageIOBase::UCHAR:
      {
      typedef unsigned char PixelType;
      typedef itk::Image< PixelType, VDimension > ImageType;

      typename ImageType::Pointer image = ImageType::New();

      if( ReadImage< ImageType >( inputFileName, image ) == EXIT_FAILURE )
        {
        return EXIT_FAILURE;
        }

      std::cout << image << std::endl;
      break;
      }

    case itk::ImageIOBase::CHAR:
      {
      typedef char PixelType;
      typedef itk::Image< PixelType, VDimension > ImageType;

      typename ImageType::Pointer image = ImageType::New();

      if( ReadImage< ImageType >( inputFileName, image ) == EXIT_FAILURE )
        {
        return EXIT_FAILURE;
        }

      std::cout << image << std::endl;
      break;
      }

    case itk::ImageIOBase::USHORT:
      {
      typedef unsigned short PixelType;
      typedef itk::Image< PixelType, VDimension > ImageType;

      typename ImageType::Pointer image = ImageType::New();

      if( ReadImage< ImageType >( inputFileName, image ) == EXIT_FAILURE )
        {
        return EXIT_FAILURE;
        }

      std::cout << image << std::endl;
      break;
      }

    case itk::ImageIOBase::SHORT:
      {
      typedef short PixelType;
      typedef itk::Image< PixelType, VDimension > ImageType;

      typename ImageType::Pointer image = ImageType::New();

      if( ReadImage< ImageType >( inputFileName, image ) == EXIT_FAILURE )
        {
        return EXIT_FAILURE;
        }

      std::cout << image << std::endl;
      break;
      }

    case itk::ImageIOBase::UINT:
      {
      typedef unsigned int PixelType;
      typedef itk::Image< PixelType, VDimension > ImageType;

      typename ImageType::Pointer image = ImageType::New();

      if( ReadImage< ImageType >( inputFileName, image ) == EXIT_FAILURE )
        {
        return EXIT_FAILURE;
        }

      std::cout << image << std::endl;
      break;
      }

    case itk::ImageIOBase::INT:
      {
      typedef int PixelType;
      typedef itk::Image< PixelType, VDimension > ImageType;

      typename ImageType::Pointer image = ImageType::New();

      if( ReadImage< ImageType >( inputFileName, image ) == EXIT_FAILURE )
        {
        return EXIT_FAILURE;
        }

      std::cout << image << std::endl;
      break;
    }

    case itk::ImageIOBase::ULONG:
      {
      typedef unsigned long PixelType;
      typedef itk::Image< PixelType, VDimension > ImageType;

      typename ImageType::Pointer image = ImageType::New();

      if( ReadImage< ImageType >( inputFileName, image ) == EXIT_FAILURE )
        {
        return EXIT_FAILURE;
        }

      std::cout << image << std::endl;
      break;
      }

    case itk::ImageIOBase::LONG:
      {
      typedef long PixelType;
      typedef itk::Image< PixelType, VDimension > ImageType;

      typename ImageType::Pointer image = ImageType::New();

      if( ReadImage< ImageType >( inputFileName, image ) == EXIT_FAILURE )
        {
        return EXIT_FAILURE;
        }

      std::cout << image << std::endl;
      break;
      }

    case itk::ImageIOBase::FLOAT:
      {
      typedef float PixelType;
      typedef itk::Image< PixelType, VDimension > ImageType;

      typename ImageType::Pointer image = ImageType::New();

      if( ReadImage< ImageType >( inputFileName, image ) == EXIT_FAILURE )
        {
        return EXIT_FAILURE;
        }

      std::cout << image << std::endl;
      break;
      }

    case itk::ImageIOBase::DOUBLE:
      {
      typedef double PixelType;
      typedef itk::Image< PixelType, VDimension > ImageType;

      typename ImageType::Pointer image = ImageType::New();

      if( ReadImage< ImageType >( inputFileName, image ) == EXIT_FAILURE )
        {
        return EXIT_FAILURE;
        }

      std::cout << image << std::endl;
      break;
      }
    }
  return EXIT_SUCCESS;
}

int main( int argc, char* argv[] )
{
  if( argc != 2 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];

  itk::ImageIOBase::Pointer imageIO =
    itk::ImageIOFactory::CreateImageIO(
      inputFileName,
      itk::ImageIOFactory::ReadMode );

  imageIO->SetFileName( inputFileName );
  imageIO->ReadImageInformation();

  typedef itk::ImageIOBase::IOPixelType     IOPixelType;
  const IOPixelType pixelType = imageIO->GetPixelType();

  std::cout << "Pixel Type is "
            << itk::ImageIOBase::GetPixelTypeAsString( pixelType )
            << std::endl;

  typedef itk::ImageIOBase::IOComponentType IOComponentType;
  const IOComponentType componentType = imageIO->GetComponentType();

  std::cout << "Component Type is "
            << imageIO->GetComponentTypeAsString( componentType )
            << std::endl;

  const unsigned int imageDimension = imageIO->GetNumberOfDimensions();

  std::cout << "Image Dimension is " << imageDimension << std::endl;

  switch( pixelType )
    {
    case itk::ImageIOBase::SCALAR:
      {
      if( imageDimension == 2 )
        {
        return ReadScalarImage< 2 >( inputFileName, componentType );
        }
      else if( imageDimension == 3 )
        {
        return ReadScalarImage< 3 >( inputFileName, componentType );
        }
      else if( imageDimension == 4 )
        {
        return ReadScalarImage< 4 >( inputFileName, componentType );
        }
      }

    default:
      std::cerr << "not implemented yet!" << std::endl;
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
