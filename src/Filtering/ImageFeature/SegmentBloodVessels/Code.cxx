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

#include "itkHessian3DToVesselnessMeasureImageFilter.h"
#include "itkHessianRecursiveGaussianImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main( int argc, char *argv[] )
{
  if( argc < 3 )
    {
    std::cerr << "Usage: <InputImage> <OutputImage> [Sigma] [Alpha1] [Alpha2]" << std::endl;
    return EXIT_FAILURE;
    }
  const char * inputImage = argv[1];
  const char * outputImage = argv[2];
  char * sigma = NULL;
  if( argc > 3 )
    {
    sigma = argv[3];
    }
  char * alpha1 = NULL;
  if( argc > 4 )
    {
    alpha1 = argv[4];
    }
  char * alpha2 = NULL;
  if( argc > 5 )
    {
    alpha2 = argv[5];
    }

  const   unsigned int        Dimension = 3;
  typedef double              InputPixelType;
  typedef float               OutputPixelType;
  typedef itk::Image< InputPixelType, Dimension >   InputImageType;
  typedef itk::Image< OutputPixelType, Dimension >  OutputImageType;

  typedef itk::ImageFileReader< InputImageType >  ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputImage );

  typedef itk::HessianRecursiveGaussianImageFilter< InputImageType >
    HessianFilterType;
  HessianFilterType::Pointer hessianFilter = HessianFilterType::New();
  hessianFilter->SetInput( reader->GetOutput() );
  if( sigma )
    {
    hessianFilter->SetSigma( atof( sigma ) );
    }

  typedef itk::Hessian3DToVesselnessMeasureImageFilter< OutputPixelType >
    VesselnessMeasureFilterType;
  VesselnessMeasureFilterType::Pointer vesselnessFilter = VesselnessMeasureFilterType::New();
  vesselnessFilter->SetInput( hessianFilter->GetOutput() );
  if( alpha1 )
    {
    vesselnessFilter->SetAlpha1( atof( alpha1 ) );
    }
  if( alpha2 )
    {
    vesselnessFilter->SetAlpha2( atof( alpha2 ) );
    }

  typedef itk::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( vesselnessFilter->GetOutput() );
  writer->SetFileName( outputImage );

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
