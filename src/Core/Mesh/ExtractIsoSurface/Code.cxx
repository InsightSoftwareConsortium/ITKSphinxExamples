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

#include "itkMesh.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkBinaryMask3DMeshSource.h"
#include "itkMeshFileWriter.h"

int main( int argc, char* argv[] )
{
  if( argc != 5 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> <Lower Threshold> <Upper Threshold>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  const unsigned int Dimension = 3;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  auto lowerThreshold = static_cast< PixelType >( atoi( argv[3] ) );
  auto upperThreshold = static_cast< PixelType >( atoi( argv[4] ) );

  typedef itk::BinaryThresholdImageFilter< ImageType, ImageType > BinaryThresholdFilterType;
  BinaryThresholdFilterType::Pointer threshold = BinaryThresholdFilterType::New();
  threshold->SetInput( reader->GetOutput() );
  threshold->SetLowerThreshold( lowerThreshold );
  threshold->SetUpperThreshold( upperThreshold );
  threshold->SetOutsideValue( 0 );

  typedef itk::Mesh< double, Dimension > MeshType;

  typedef itk::BinaryMask3DMeshSource< ImageType, MeshType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( threshold->GetOutput() );
  filter->SetObjectValue( 255 );

  typedef itk::MeshFileWriter< MeshType > WriterType;
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
