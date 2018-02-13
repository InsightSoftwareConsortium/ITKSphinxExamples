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
#include "itkTileImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc < 3 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << "<input1> <input2> <input3> ... <output>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  constexpr unsigned int InputDimension = 2;
  constexpr unsigned int OutputDimension = 3;

  using PixelType = unsigned char;
  using InputImageType = itk::Image< PixelType, InputDimension >;
  using OutputImageType = itk::Image< PixelType, OutputDimension >;

  using ReaderType = itk::ImageFileReader< InputImageType >;
  ReaderType::Pointer reader = ReaderType::New();

  using FilterType = itk::TileImageFilter< InputImageType, OutputImageType >;
  FilterType::Pointer filter = FilterType::New();

  itk::FixedArray< unsigned int, OutputDimension > layout;
  layout[0] = 2;
  layout[1] = 2;
  layout[2] = 0;

  filter->SetLayout( layout );

  for( int ii = 1; ii < argc - 1; ++ii )
    {
    reader->SetFileName( argv[ii] );

    try
      {
      reader->Update();
      }
    catch( itk::ExceptionObject & e )
      {
      std::cerr << e << std::endl;
      return EXIT_FAILURE;
      }

    InputImageType::Pointer input = reader->GetOutput();
    input->DisconnectPipeline();

    filter->SetInput( ii - 1, input );
    }

  constexpr PixelType defaultValue  = 128;

  filter->SetDefaultPixelValue( defaultValue );

  using WriterType = itk::ImageFileWriter< OutputImageType >;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[ argc - 1 ] );
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
