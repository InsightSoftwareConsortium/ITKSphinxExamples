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
#include "itkLinearInterpolateImageFunction.h"
#include "itkResampleImageFilter.h"
#include "itkScaleTransform.h"

int main( int argc, char* argv[] )
{
  if( argc != 4 )
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
  const float scale = atof( argv[3] );

  const unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image< PixelType, Dimension >;
  using ScalarType = double;

  using ReaderType = itk::ImageFileReader< ImageType >;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );
  reader->Update();

  ImageType::Pointer inputImage = reader->GetOutput();

  ImageType::RegionType region = inputImage->GetLargestPossibleRegion();
  ImageType::SizeType size = region.GetSize();
  ImageType::SpacingType spacing = inputImage->GetSpacing();

  itk::Index< Dimension > centralPixel;
  centralPixel[0] = size[0] / 2;
  centralPixel[1] = size[1] / 2;
  itk::Point< ScalarType, Dimension > centralPoint;
  centralPoint[0] = centralPixel[0];
  centralPoint[1] = centralPixel[1];

  using ScaleTransformType = itk::ScaleTransform< ScalarType, Dimension >;
  ScaleTransformType::Pointer scaleTransform = ScaleTransformType::New();

  ScaleTransformType::ParametersType parameters = scaleTransform->GetParameters();
  parameters[0] = scale;
  parameters[1] = scale;

  scaleTransform->SetParameters( parameters );
  scaleTransform->SetCenter( centralPoint );

  using LinearInterpolatorType = itk::LinearInterpolateImageFunction< ImageType, ScalarType >;
  LinearInterpolatorType::Pointer interpolator = LinearInterpolatorType::New();

  using ResampleFilterType = itk::ResampleImageFilter< ImageType, ImageType >;
  ResampleFilterType::Pointer resampleFilter = ResampleFilterType::New();

  resampleFilter->SetInput( inputImage );
  resampleFilter->SetTransform( scaleTransform );
  resampleFilter->SetInterpolator( interpolator );
  resampleFilter->SetSize( size );
  resampleFilter->SetOutputSpacing( spacing );

  using WriterType = itk::ImageFileWriter< ImageType >;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
  writer->SetInput( resampleFilter->GetOutput() );

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
