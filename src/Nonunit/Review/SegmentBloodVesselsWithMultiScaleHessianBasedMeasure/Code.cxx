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
#include "itkHessianToObjectnessMeasureImageFilter.h"
#include "itkMultiScaleHessianBasedMeasureImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc < 3 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << " [SigmaMinimum] [SigmaMaximum]";
    std::cerr << " [NumberOfSigmaSteps]";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];
  double sigmaMinimum = 1.0;
  if( argc > 3 )
    {
    sigmaMinimum = atof( argv[3] );
    }
  double sigmaMaximum = 10.0;
  if( argc > 4 )
    {
    sigmaMaximum = atof( argv[4] );
    }
  unsigned int numberOfSigmaSteps = 10;
  if( argc > 5 )
    {
    numberOfSigmaSteps = atoi( argv[5] );
    }

  const unsigned int Dimension = 2;

  typedef float                              PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  typedef itk::SymmetricSecondRankTensor< double, Dimension > HessianPixelType;
  typedef itk::Image< HessianPixelType, Dimension >           HessianImageType;
  typedef itk::HessianToObjectnessMeasureImageFilter< HessianImageType, ImageType >
    ObjectnessFilterType;
  ObjectnessFilterType::Pointer objectnessFilter = ObjectnessFilterType::New();
  objectnessFilter->SetBrightObject( false );
  objectnessFilter->SetScaleObjectnessMeasure( false );
  objectnessFilter->SetAlpha( 0.5 );
  objectnessFilter->SetBeta( 1.0 );
  objectnessFilter->SetGamma( 5.0 );

  typedef itk::MultiScaleHessianBasedMeasureImageFilter< ImageType, HessianImageType, ImageType >
    MultiScaleEnhancementFilterType;
  MultiScaleEnhancementFilterType::Pointer multiScaleEnhancementFilter =
    MultiScaleEnhancementFilterType::New();
  multiScaleEnhancementFilter->SetInput( reader->GetOutput() );
  multiScaleEnhancementFilter->SetHessianToMeasureFilter( objectnessFilter );
  multiScaleEnhancementFilter->SetSigmaStepMethodToLogarithmic();
  multiScaleEnhancementFilter->SetSigmaMinimum( sigmaMinimum );
  multiScaleEnhancementFilter->SetSigmaMaximum( sigmaMaximum );
  multiScaleEnhancementFilter->SetNumberOfSigmaSteps( numberOfSigmaSteps );

  typedef itk::Image< unsigned char, Dimension > OutputImageType;
  typedef itk::RescaleIntensityImageFilter< ImageType, OutputImageType >
    RescaleFilterType;
  RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
  rescaleFilter->SetInput( multiScaleEnhancementFilter->GetOutput() );

  typedef itk::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( rescaleFilter->GetOutput() );

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
