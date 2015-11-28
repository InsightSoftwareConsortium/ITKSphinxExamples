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
#include "itkImageFileWriter.h"
#include "itkBinaryErodeImageFilter.h"
#include "itkFlatStructuringElement.h"

int main( int argc, char* argv[] )
{
  if( argc < 4 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " <inputImage> <outputImage> <radius>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }
  const char * inputImage = argv[1];
  const char * outputImage = argv[2];
  const unsigned int radiusValue = atoi( argv[3] );

  typedef unsigned char PixelType;
  const unsigned int Dimension = 2;

  typedef itk::Image< PixelType, Dimension >    ImageType;
  typedef itk::ImageFileReader< ImageType >     ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputImage );

  typedef itk::FlatStructuringElement< Dimension >
    StructuringElementType;
  StructuringElementType::RadiusType radius;
  radius.Fill( radiusValue );
  StructuringElementType structuringElement =
    StructuringElementType::Ball( radius );

  typedef itk::BinaryErodeImageFilter< ImageType, ImageType,
    StructuringElementType > BinaryErodeImageFilterType;

  BinaryErodeImageFilterType::Pointer erodeFilter =
    BinaryErodeImageFilterType::New();
  erodeFilter->SetInput( reader->GetOutput() );
  erodeFilter->SetKernel( structuringElement );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( erodeFilter->GetOutput() );
  writer->SetFileName( outputImage );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & e )
    {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
