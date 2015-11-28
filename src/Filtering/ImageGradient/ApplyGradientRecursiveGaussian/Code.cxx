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
  typedef unsigned char                              PixelType;
  typedef itk::Image< PixelType, Dimension >         ImageType;
  // Double type for GradientRecursiveGaussianImageFilter
  typedef double                                     DoublePixelType;
  typedef itk::Image< DoublePixelType, Dimension >   DoubleImageType;
  // The output of GradientRecursiveGaussianImageFilter
  // are images of the gradient along X and Y, so the type of
  // the output is a covariant vector of dimension 2 (X, Y)
  typedef itk::CovariantVector< DoublePixelType, Dimension > CovPixelType;
  typedef itk::Image< CovPixelType, Dimension >              CovImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  typedef itk::GradientRecursiveGaussianImageFilter< ImageType, CovImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );

  // Allows to select the X or Y output images
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
  for( int i = 0; i<2 ;++i )
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
  typedef itk::VectorMagnitudeImageFilter< CovImageType, DoubleImageType > MagnitudeType;
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
