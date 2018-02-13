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

#include "itkMesh.h"
#include "itkMeshFileReader.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkCastImageFilter.h"
#include "itkTriangleMeshToBinaryImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 4 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputImageName> <InputMeshName> <OutputImageName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputImageName   = argv[1];
  const char * inputMeshName    = argv[2];
  const char * outputImageName  = argv[3];

  const unsigned int Dimension = 3;
  using MeshPixelType = double;

  using MeshType = itk::Mesh< MeshPixelType, Dimension >;

  using MeshReaderType = itk::MeshFileReader< MeshType >;
  MeshReaderType::Pointer meshReader = MeshReaderType::New();
  meshReader->SetFileName( inputMeshName );

  using InputPixelType = unsigned char;
  using InputImageType = itk::Image< InputPixelType, Dimension >;
  using ImageReaderType = itk::ImageFileReader< InputImageType >;

  ImageReaderType::Pointer imageReader = ImageReaderType::New();
  imageReader->SetFileName( inputImageName );

  using OutputPixelType = unsigned char;
  using OutputImageType = itk::Image< OutputPixelType, Dimension >;

  using CastFilterType = itk::CastImageFilter< InputImageType, OutputImageType >;
  CastFilterType::Pointer cast = CastFilterType::New();
  cast->SetInput( imageReader->GetOutput() );

  using FilterType = itk::TriangleMeshToBinaryImageFilter< MeshType, OutputImageType >;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( meshReader->GetOutput() );
  filter->SetInfoImage( cast->GetOutput() );
  filter->SetInsideValue( itk::NumericTraits< OutputPixelType >::max() );
  try
    {
    filter->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  using WriterType = itk::ImageFileWriter< OutputImageType >;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputImageName );
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
