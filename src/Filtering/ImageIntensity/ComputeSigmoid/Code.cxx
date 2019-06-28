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
#include "itkSigmoidImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 7 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << " <OutputMin> <OutputMax> <Alpha> <Beta>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image< PixelType, Dimension >;
  using ScalarType = float;

  const auto outputMinimum = static_cast<PixelType>(atoi( argv[3] ) );
  const auto outputMaximum = static_cast<PixelType>(atoi( argv[4] ) );
  const ScalarType alpha = std::stod( argv[5] );
  const ScalarType beta  = std::stod( argv[6] );

  using ReaderType = itk::ImageFileReader< ImageType >;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  using FilterType = itk::SigmoidImageFilter< ImageType, ImageType >;
  FilterType::Pointer sigmoidFilter = FilterType::New();
  sigmoidFilter->SetInput( reader->GetOutput() );
  sigmoidFilter->SetOutputMinimum( outputMinimum );
  sigmoidFilter->SetOutputMaximum( outputMaximum );
  sigmoidFilter->SetAlpha( alpha );
  sigmoidFilter->SetBeta( beta );

  using WriterType = itk::ImageFileWriter< ImageType >;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( sigmoidFilter->GetOutput() );

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
