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
#include "itkGradientRecursiveGaussianImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkVectorIndexSelectionCastImageFilter.h"
#include "itkVectorMagnitudeImageFilter.h"
#include "itkInvertIntensityImageFilter.h"
#include "itkComposeImageFilter.h"
#include "itkCastImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 6 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName1X> <OutputFileName1Y> <OutputFileName2X> <OutputFileName2Y>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName =    argv[1];
  const char * outputFileName1X = argv[2];
  const char * outputFileName1Y = argv[3];
  const char * outputFileName2X = argv[4];
  const char * outputFileName2Y = argv[5];

  const char *filenames [4];
  filenames[0] = outputFileName1X;
  filenames[1] = outputFileName1Y;
  filenames[2] = outputFileName2X;
  filenames[3] = outputFileName2Y;

  const unsigned int ImageDimension =  2;
  const unsigned int VectorDimension = 2;
  const unsigned int CovDimension =    4;

  typedef unsigned char                                           PixelType;
  typedef itk::Image< PixelType, ImageDimension >                 ImageType;
  typedef double                                                  DoublePixelType;
  typedef itk::Image< DoublePixelType, ImageDimension >           DoubleImageType;
  typedef itk::Vector< DoublePixelType, VectorDimension >         VecPixelType;
  typedef itk::Image< VecPixelType, ImageDimension >              VecImageType;
  typedef itk::CovariantVector< DoublePixelType, CovDimension >   CovPixelType;
  typedef itk::Image< CovPixelType, ImageDimension >              CovImageType;

  typedef itk::ImageFileReader< ImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  // Invert the input image
  typedef itk::InvertIntensityImageFilter< ImageType, ImageType > InvertType;
  InvertType::Pointer inverter = InvertType::New();
  inverter->SetInput( reader->GetOutput() );

  // Cast the image to double type.
  typedef itk::CastImageFilter< ImageType, DoubleImageType > CasterType;
  CasterType::Pointer caster = CasterType::New();
  CasterType::Pointer caster2 = CasterType::New();

  // Create an image, were each pixel has 2 values: first value is the value
  // coming from the input image, second value is coming from the inverted
  // image
  typedef itk::ComposeImageFilter< DoubleImageType, VecImageType > ComposeType;
  ComposeType::Pointer composer = ComposeType::New();
  caster->SetInput( reader->GetOutput() );
  composer->SetInput( 0, caster->GetOutput() );
  caster2->SetInput( inverter->GetOutput() );
  composer->SetInput( 1, caster2->GetOutput() );

  // Apply the gradient filter on the two images, this will return and image
  // with 4 values per pixel: two X and Y gradients
  typedef itk::GradientRecursiveGaussianImageFilter< VecImageType, CovImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( composer->GetOutput() );

  // Set up the filter to select each gradient
  typedef itk::VectorIndexSelectionCastImageFilter< CovImageType, DoubleImageType > IndexSelectionType;
  IndexSelectionType::Pointer indexSelectionFilter = IndexSelectionType::New();
  indexSelectionFilter->SetInput( filter->GetOutput() );

  // Rescale for png output
  typedef itk::RescaleIntensityImageFilter< DoubleImageType, ImageType > RescalerType;
  RescalerType::Pointer rescaler = RescalerType::New();
  rescaler->SetOutputMinimum( itk::NumericTraits< PixelType >::min() );
  rescaler->SetOutputMaximum( itk::NumericTraits< PixelType >::max() );
  rescaler->SetInput( indexSelectionFilter->GetOutput() );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( rescaler->GetOutput() );

  // Write the X and Y images
  for( int i = 0; i<4 ;++i )
  {
    indexSelectionFilter->SetIndex( i );
    writer->SetFileName( filenames[i] );

    try
    {
      writer->Update();
    }
    catch( itk::ExceptionObject & error )
    {
      std::cerr << "Error: " << error << std::endl;
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
