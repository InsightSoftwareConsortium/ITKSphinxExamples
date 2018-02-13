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
#include "itkTileImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 4 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName1> <InputFileName2> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }
  const char * inputFileName1 = argv[1];
  const char * inputFileName2 = argv[2];
  const char * outputFileName = argv[3];

  const unsigned int Dimension = 3;

  using PixelType = unsigned char;
  using ImageType = itk::Image< PixelType, Dimension >;

  using ReaderType = itk::ImageFileReader< ImageType >;
  ReaderType::Pointer reader1 = ReaderType::New();
  reader1->SetFileName( inputFileName1 );

  using ReaderType = itk::ImageFileReader< ImageType >;
  ReaderType::Pointer reader2 = ReaderType::New();
  reader2->SetFileName( inputFileName2 );

  using TileFilterType = itk::TileImageFilter< ImageType, ImageType >;
  TileFilterType::Pointer tileFilter = TileFilterType::New();
  tileFilter->SetInput( 0, reader1->GetOutput() );
  tileFilter->SetInput( 1, reader2->GetOutput() );
  TileFilterType::LayoutArrayType layout;
  layout[0] = 1;
  layout[1] = 1;
  layout[2] = 2;
  tileFilter->SetLayout( layout );

  using WriterType = itk::ImageFileWriter< ImageType >;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( tileFilter->GetOutput() );
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
