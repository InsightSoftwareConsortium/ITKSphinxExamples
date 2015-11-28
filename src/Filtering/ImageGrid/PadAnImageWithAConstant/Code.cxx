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
#include "itkConstantPadImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 6 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << "<InputFileName> <OutputFileName> <LowerExtendSize> ";
    std::cerr << "<UpperExtendSize> <ConstantValue>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef unsigned char                       PixelType;
  typedef itk::Image< PixelType, Dimension >  ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  ImageType::SizeType lowerExtendRegion;
  lowerExtendRegion.Fill( atoi( argv[3] ) );

  ImageType::SizeType upperExtendRegion;
  upperExtendRegion.Fill( atoi( argv[4] ) );

  typedef itk::ConstantPadImageFilter< ImageType, ImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetPadLowerBound(lowerExtendRegion);
  filter->SetPadUpperBound(upperExtendRegion);
  filter->SetConstant( atoi( argv[5] ) );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[2] );
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
