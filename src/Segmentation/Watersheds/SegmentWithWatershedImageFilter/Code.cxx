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
#include "itkScalarToRGBPixelFunctor.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkVectorCastImageFilter.h"
#include "itkVectorGradientAnisotropicDiffusionImageFilter.h"
#include "itkWatershedImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkGradientMagnitudeImageFilter.h"

// Run with:
// ./WatershedImageFilter threshold level
// e.g.
// ./WatershedImageFilter 0.005 .5
// (A rule of thumb is to set the Threshold to be about 1 / 100 of the Level.)

int main( int argc, char *argv[] )
{
  if( argc < 5 )
    {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << argv[0]
      << " inputImageFile outputImageFile threshold level" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef itk::Image< unsigned char, Dimension >        InputImageType;
  typedef itk::Image< float, Dimension >                FloatImageType;
  typedef itk::RGBPixel< unsigned char >                RGBPixelType;
  typedef itk::Image< RGBPixelType, Dimension >         RGBImageType;
  typedef itk::Image< itk::IdentifierType, Dimension >  LabeledImageType;

  typedef itk::ImageFileReader< InputImageType > FileReaderType;
  FileReaderType::Pointer reader = FileReaderType::New();
  reader->SetFileName( argv[1] );

  typedef itk::GradientMagnitudeImageFilter< InputImageType, FloatImageType >
    GradientMagnitudeImageFilterType;
  GradientMagnitudeImageFilterType::Pointer gradientMagnitudeImageFilter =
    GradientMagnitudeImageFilterType::New();

  gradientMagnitudeImageFilter->SetInput( reader->GetOutput() );
  gradientMagnitudeImageFilter->Update();

  typedef itk::WatershedImageFilter< FloatImageType > WatershedFilterType;
  WatershedFilterType::Pointer watershed = WatershedFilterType::New();

  float threshold = atof( argv[3] );
  float level = atof( argv[4] );

  watershed->SetThreshold( threshold );
  watershed->SetLevel( level );

  watershed->SetInput( gradientMagnitudeImageFilter->GetOutput() );
  watershed->Update();

  typedef itk::ScalarToRGBColormapImageFilter< LabeledImageType, RGBImageType>
    RGBFilterType;
  RGBFilterType::Pointer colormapImageFilter = RGBFilterType::New();
  colormapImageFilter->SetColormap( RGBFilterType::Jet );
  colormapImageFilter->SetInput( watershed->GetOutput() );
  colormapImageFilter->Update();

  typedef itk::ImageFileWriter< RGBImageType > FileWriterType;
  FileWriterType::Pointer writer = FileWriterType::New();
  writer->SetFileName( argv[2] );
  writer->SetInput( colormapImageFilter->GetOutput() );
  writer->Update();

  return EXIT_SUCCESS;
}