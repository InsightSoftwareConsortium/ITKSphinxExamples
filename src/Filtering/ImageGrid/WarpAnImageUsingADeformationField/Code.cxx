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
#include "itkVector.h"
#include "itkWarpImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc < 4)
    {
    std::cerr << "Usage: \n"
              << argv[0]
              << "<InputFileName> <DisplacementFieldFileName> <OutputFileName>"
              << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * displacementFieldFileName = argv[2];
  const char * outputFileName = argv[3];

  const unsigned int Dimension = 2;

  typedef float VectorComponentType;
  typedef itk::Vector< VectorComponentType, Dimension > VectorPixelType;

  typedef itk::Image< VectorPixelType, Dimension > DisplacementFieldType;

  typedef unsigned char PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::ImageFileReader< ImageType > ReaderType;
  typedef itk::ImageFileWriter< ImageType > WriterType;

  typedef itk::ImageFileReader< DisplacementFieldType > FieldReaderType;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  FieldReaderType::Pointer fieldReader = FieldReaderType::New();
  fieldReader->SetFileName( displacementFieldFileName );
  fieldReader->Update();

  DisplacementFieldType::ConstPointer deformationField = fieldReader->GetOutput();

  typedef itk::WarpImageFilter< ImageType, ImageType, DisplacementFieldType > FilterType;

  FilterType::Pointer filter = FilterType::New();

  typedef itk::LinearInterpolateImageFunction< ImageType, double > InterpolatorType;

  InterpolatorType::Pointer interpolator = InterpolatorType::New();

  filter->SetInterpolator( interpolator );

  filter->SetOutputSpacing( deformationField->GetSpacing() );
  filter->SetOutputOrigin( deformationField->GetOrigin() );
  filter->SetOutputDirection( deformationField->GetDirection() );

  filter->SetDisplacementField( deformationField );

  filter->SetInput( reader->GetOutput() );

  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName( outputFileName );

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
