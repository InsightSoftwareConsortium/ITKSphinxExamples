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
#include "itkLabelObject.h"
#include "itkLabelMap.h"
#include "itkLabelImageToLabelMapFilter.h"
#include "itkLabelMapMaskImageFilter.h"

int main( int argc, char* argv[] )
{
  if( ( argc != 6 ) && ( argc != 9 ) )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <LabelMapFileName> <OutputFileName> <Label> <Background>";
    std::cerr << " [<negated (bool)> <crop (bool)> <border size>]";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef unsigned char                      PixelType;
  typedef itk::Image< PixelType, Dimension > ImageType;

  const char * inputFileName = argv[1];
  const char * labelMapFileName = argv[2];
  const char * outputFileName = argv[3];
  const auto label = static_cast< PixelType >( atoi( argv[4] ) );
  const auto background = static_cast< PixelType >( atoi( argv[5] ) );
  bool negated                              = false;
  bool crop                                 = false;
  ImageType::SizeValueType borderSize = 0;

  if( argc == 9 )
  {
    negated = ( atoi( argv[6] ) == 1 );
    crop    = ( atoi( argv[7] ) == 1 );
    borderSize = static_cast< ImageType::SizeValueType >( atoi( argv[8] ) );
  }

  typedef itk::ImageFileReader< ImageType >  ReaderType;
  ReaderType::Pointer reader1 = ReaderType::New();
  reader1->SetFileName( inputFileName );

  ReaderType::Pointer reader2 = ReaderType::New();
  reader2->SetFileName( labelMapFileName );

  typedef itk::LabelObject< PixelType, Dimension >  LabelObjectType;
  typedef itk::LabelMap< LabelObjectType >          LabelMapType;

  // convert the label image into a LabelMap
  typedef itk::LabelImageToLabelMapFilter< ImageType, LabelMapType > LabelImage2LabelMapType;
  LabelImage2LabelMapType::Pointer convert = LabelImage2LabelMapType::New();
  convert->SetInput( reader2->GetOutput() );

  typedef itk::LabelMapMaskImageFilter< LabelMapType, ImageType > FilterType;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( convert->GetOutput() );
  filter->SetFeatureImage( reader1->GetOutput() );

  // The label to be used to mask the image is passed via SetLabel
  filter->SetLabel( label );

  // The background in the output image (where the image is masked)
  // is passed via SetBackground
  filter->SetBackgroundValue( background );

  // The user can choose to mask the image outside the label object
  // (default behavior), or inside the label object with the chosen label,
  // by calling SetNegated().
  filter->SetNegated( negated );

  // Finally, the image can be cropped to the masked region, by calling
  // SetCrop( true ), or to a region padded by a border, by calling both
  // SetCrop() and SetCropBorder().
  // The crop border defaults to 0, and the image is not cropped by default.
  filter->SetCrop( crop );

  FilterType::SizeType border;
  border.Fill( borderSize );

  filter->SetCropBorder( border );

  typedef itk::ImageFileWriter< ImageType > WriterType;
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
