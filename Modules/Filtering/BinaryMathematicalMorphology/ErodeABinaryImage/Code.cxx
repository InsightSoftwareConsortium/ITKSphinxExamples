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
#include "itkBinaryBallStructuringElement.h"

int main( int argc, char* argv[] )
{
  if( argc < 4 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " <inputImage> <outputImage> <radius>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }
  typedef unsigned char PixelType;
  const unsigned int Dimension = 2;

  typedef itk::Image< PixelType, Dimension >    ImageType;
  typedef itk::ImageFileReader< ImageType >     ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  typedef itk::BinaryBallStructuringElement< PixelType, Dimension >
    StructuringElementType;
  StructuringElementType structuringElement;
  structuringElement.SetRadius( atoi( argv[3] ) );
  structuringElement.CreateStructuringElement();

  typedef itk::BinaryErodeImageFilter< ImageType, ImageType,
    StructuringElementType > BinaryErodeImageFilterType;

  BinaryErodeImageFilterType::Pointer dilateFilter =
    BinaryErodeImageFilterType::New();
  dilateFilter->SetInput( reader->GetOutput() );
  dilateFilter->SetKernel( structuringElement );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( dilateFilter->GetOutput() );
  writer->SetFileName( argv[2] );

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
