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

int main( int argc, char* argv[] )
{
  if( argc != 5 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileNameX> <OutputFileNameY> <OutputFileNameMagnitude>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName =           argv[1];
  const char * outputFileNameX =         argv[2];
  const char * outputFileNameY =         argv[3];
  const char * outputFileNameMagnitude = argv[4];

  const char *filenames [2];
  filenames[0] = outputFileNameX;
  filenames[1] = outputFileNameY;

  const unsigned int Dimension = 2;

  // Input and output are png files, use unsigned char
  using PixelType = unsigned char;
  using ImageType = itk::Image< PixelType, Dimension >;
  // Double type for GradientRecursiveGaussianImageFilter
  using DoublePixelType = double;
  using DoubleImageType = itk::Image< DoublePixelType, Dimension >;
  // The output of GradientRecursiveGaussianImageFilter
  // are images of the gradient along X and Y, so the type of
  // the output is a covariant vector of dimension 2 (X, Y)
  using CovPixelType = itk::CovariantVector< DoublePixelType, Dimension >;
  using CovImageType = itk::Image< CovPixelType, Dimension >;

  using ReaderType = itk::ImageFileReader< ImageType >;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  using FilterType = itk::GradientRecursiveGaussianImageFilter< ImageType, CovImageType >;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );

  // Allows to select the X or Y output images
  using IndexSelectionType = itk::VectorIndexSelectionCastImageFilter< CovImageType, DoubleImageType >;
  IndexSelectionType::Pointer indexSelectionFilter = IndexSelectionType::New();
  indexSelectionFilter->SetInput( filter->GetOutput() );

  // Rescale for png output
  using RescalerType = itk::RescaleIntensityImageFilter< DoubleImageType, ImageType >;
  RescalerType::Pointer rescaler = RescalerType::New();
  rescaler->SetOutputMinimum( itk::NumericTraits< PixelType >::min() );
  rescaler->SetOutputMaximum( itk::NumericTraits< PixelType >::max() );
  rescaler->SetInput( indexSelectionFilter->GetOutput() );

  using WriterType = itk::ImageFileWriter< ImageType >;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( rescaler->GetOutput() );

  // Write the X and Y images
  for( int i = 0; i<2;++i )
  {

    writer->SetFileName( filenames[i] );
    indexSelectionFilter->SetIndex( i );

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

  // Compute the magnitude of the vector and output the image
  using MagnitudeType = itk::VectorMagnitudeImageFilter< CovImageType, DoubleImageType >;
  MagnitudeType::Pointer magnitudeFilter = MagnitudeType::New();
  magnitudeFilter->SetInput( filter->GetOutput() );

  // Rescale for png output
  rescaler->SetInput( magnitudeFilter->GetOutput() );

  writer->SetFileName( outputFileNameMagnitude );
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
