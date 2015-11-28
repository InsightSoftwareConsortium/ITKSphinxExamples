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
#include "itkMultiplyImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 4 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName 1> <InputFileName 2> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName1 = argv[1];
  const char * inputFileName2 = argv[2];
  const char * outputFileName = argv[3];

  const unsigned int Dimension = 2;

  typedef unsigned char                           InputPixelType;
  typedef itk::Image< InputPixelType, Dimension > InputImageType;

  typedef itk::ImageFileReader< InputImageType >  ReaderType;
  ReaderType::Pointer reader1 = ReaderType::New();
  reader1->SetFileName( inputFileName1 );

  ReaderType::Pointer reader2 = ReaderType::New();
  reader2->SetFileName( inputFileName2 );

  typedef unsigned int                              OutputPixelType;
  typedef itk::Image< OutputPixelType, Dimension >  OutputImageType;

  typedef itk::MultiplyImageFilter< InputImageType, InputImageType, OutputImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput1( reader1->GetOutput() );
  filter->SetInput2( reader2->GetOutput() );

  typedef itk::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( filter->GetOutput() );
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
