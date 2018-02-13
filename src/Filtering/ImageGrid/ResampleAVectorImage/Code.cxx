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
#include "itkResampleImageFilter.h"
#include "itkIdentityTransform.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkRGBPixel.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  const unsigned int Dimension = 2;

  using PixelComponentType = unsigned char;
  using PixelType = itk::RGBPixel< PixelComponentType >;
  using ImageType = itk::Image< PixelType,  Dimension >;

  using ReaderType = itk::ImageFileReader< ImageType >;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  using FilterType = itk::ResampleImageFilter< ImageType, ImageType >;

  FilterType::Pointer filter = FilterType::New();

  using InterpolatorType = itk::LinearInterpolateImageFunction< ImageType, double >;

  InterpolatorType::Pointer interpolator = InterpolatorType::New();

  filter->SetInterpolator( interpolator );

  using TransformType = itk::IdentityTransform< double, Dimension >;
  TransformType::Pointer transform = TransformType::New();

  filter->SetTransform( transform );

  PixelType defaultValue;
  defaultValue.Fill(50);
  filter->SetDefaultPixelValue( defaultValue );

  ImageType::SpacingType spacing;
  spacing[0] = .5; // pixel spacing in millimeters along X
  spacing[1] = .5; // pixel spacing in millimeters along Y

  filter->SetOutputSpacing( spacing );

  ImageType::PointType origin;
  origin[0] = 30.0;  // X space coordinate of origin
  origin[1] = 40.0;  // Y space coordinate of origin
  filter->SetOutputOrigin( origin );

  ImageType::DirectionType direction;
  direction.SetIdentity();
  filter->SetOutputDirection( direction );

  ImageType::SizeType   size;

  size[0] = 300;  // number of pixels along X
  size[1] = 300;  // number of pixels along Y

  filter->SetSize( size );
  filter->SetInput( reader->GetOutput() );

  using WriterType = itk::ImageFileWriter< ImageType >;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputFileName );
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
