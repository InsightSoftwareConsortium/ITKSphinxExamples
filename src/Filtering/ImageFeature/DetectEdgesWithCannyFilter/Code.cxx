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
#include "itkCannyEdgeDetectionImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 6 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << "<InputImage> <OutputImage> ";
    std::cerr << "<Variance> <UpperThreshold> <LowerThreshold>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int      Dimension = 2;
  typedef  float          InputPixelType;
  typedef  unsigned char  OutputPixelType;

  typedef itk::Image<InputPixelType, Dimension>  InputImageType;
  typedef itk::Image<OutputPixelType, Dimension> OutputImageType;

  const char * InputImage = argv[1];
  const char * OutputImage = argv[2];
  const InputPixelType variance = atof( argv[3] );
  const InputPixelType upperThreshold = atof( argv[4] );
  const InputPixelType lowerThreshold = atof( argv[5] );

  typedef itk::ImageFileReader< InputImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( InputImage );

  typedef itk::CannyEdgeDetectionImageFilter< InputImageType, InputImageType >
    FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetVariance( variance );
  filter->SetUpperThreshold( upperThreshold );
  filter->SetLowerThreshold( lowerThreshold );

  typedef itk::RescaleIntensityImageFilter< InputImageType, OutputImageType > RescaleType;
  RescaleType::Pointer rescaler = RescaleType::New();
  rescaler->SetInput( filter->GetOutput() );
  rescaler->SetOutputMinimum( 0 );
  rescaler->SetOutputMaximum( 255 );

  typedef itk::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( OutputImage );
  writer->SetInput( rescaler->GetOutput() );

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
