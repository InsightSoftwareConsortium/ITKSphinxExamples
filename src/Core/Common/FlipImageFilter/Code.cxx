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
#include "itkImage.h"
#include "itkFlipImageFilter.h"

int main( int argc, char* argv[] )
{
 if( argc < 5 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputImageFile   outputImageFile   flipAxisX   flipAxisY" << std::endl;
    return EXIT_FAILURE;
    }

  typedef   unsigned char  PixelType;
  typedef itk::Image< PixelType,  2 >   ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  typedef itk::ImageFileWriter< ImageType >  WriterType;
  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();
  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );

  typedef itk::FlipImageFilter< ImageType >  FilterType;
  FilterType::Pointer filter = FilterType::New();

  typedef FilterType::FlipAxesArrayType FlipAxesArrayType;
  FlipAxesArrayType flipArray(2);
  flipArray[0] = atoi( argv[3] );
  flipArray[1] = atoi( argv[4] );
  filter->SetFlipAxes( flipArray );

  filter->SetInput( reader->GetOutput() );
  writer->SetInput( filter->GetOutput() );
  writer->Update();

  return EXIT_SUCCESS;
}
