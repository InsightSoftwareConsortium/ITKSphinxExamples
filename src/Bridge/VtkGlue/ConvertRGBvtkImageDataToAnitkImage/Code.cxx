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

#include "vtkSmartPointer.h"
#include "vtkPNGReader.h"
#include "itkVTKImageToImageFilter.h"
#include "itkRGBPixel.h"

int main( int argc, char* argv[] )
{
  if( argc != 2 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];

  const unsigned int Dimension = 2;

  typedef unsigned char                       PixelComponentType;
  typedef itk::RGBPixel< PixelComponentType > PixelType;
  typedef itk::Image< PixelType, Dimension  > ImageType;

  vtkSmartPointer< vtkPNGReader > reader =
    vtkSmartPointer< vtkPNGReader >::New();
  reader->SetFileName( inputFileName );
  reader->SetDataScalarTypeToUnsignedChar();

  typedef itk::VTKImageToImageFilter< ImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );

   try
     {
     reader->Update();
     filter->Update();
     }
   catch( itk::ExceptionObject & error )
     {
     std::cerr << "Error: " << error << std::endl;
     return EXIT_FAILURE;
     }

  ImageType::ConstPointer myitkImage = filter->GetOutput();
  myitkImage->Print(std::cout);

  return EXIT_SUCCESS;
}
