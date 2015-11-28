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
#include "itkCurvatureAnisotropicDiffusionImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 6 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << " <numberOfIterations> <timeStep> <conductance>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  const unsigned int Dimension = 2;

  typedef float                                    InputPixelType;
  typedef itk::Image< InputPixelType, Dimension >  InputImageType;
  typedef unsigned char                            OutputPixelType;
  typedef itk::Image< OutputPixelType, Dimension > OutputImageType;

  const int numberOfIterations     = atoi( argv[3] );
  const InputPixelType timeStep    = atof( argv[4] );
  const InputPixelType conductance = atof( argv[5] );

  typedef itk::ImageFileReader< InputImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  typedef itk::CurvatureAnisotropicDiffusionImageFilter< InputImageType, InputImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );
  filter->SetNumberOfIterations( numberOfIterations );
  filter->SetTimeStep( timeStep );
  filter->SetConductanceParameter( conductance );

  typedef itk::RescaleIntensityImageFilter< InputImageType, OutputImageType > RescaleType;
  RescaleType::Pointer rescaler = RescaleType::New();
  rescaler->SetInput( filter->GetOutput() );
  rescaler->SetOutputMinimum( itk::NumericTraits< OutputPixelType >::min() );
  rescaler->SetOutputMaximum( itk::NumericTraits< OutputPixelType >::max() );

  typedef itk::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( rescaler->GetOutput() );

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
