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
#include "itkVersor.h"
#include "itkChangeInformationImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc < 2 )
    {
    std::cerr << "Usage: "
              << argv[0] << " <inputFileName>"
              << " [scalingFactor]"
              << " [translationX translationY translationZ]"
              << " [rotationZinDegrees]" << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  double scalingFactor = 1.0;
  if( argc > 3 )
    {
    scalingFactor = atof( argv[3] );
    }
  double translationX = 0.0;
  if( argc > 3 )
    {
    translationX = atof( argv[3] );
    }
  double translationY = 0.0;
  if( argc > 4 )
    {
    translationY = atof( argv[4] );
    }
  double translationZ = 0.0;
  if( argc > 5 )
    {
    translationZ = atof( argv[5] );
    }
  double rotationZ = 0.0;
  if( argc > 6 )
    {
    rotationZ = atof( argv[6] );
    }

  constexpr unsigned int Dimension = 3;

  using PixelType = unsigned char;
  using ImageType = itk::Image< PixelType, Dimension >;

  using ReaderType = itk::ImageFileReader< ImageType >;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );
  try
    {
    reader->UpdateOutputInformation();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }
  ImageType::ConstPointer inputImage = reader->GetOutput();
  std::cout << "Original image: " << inputImage << std::endl;

  using FilterType = itk::ChangeInformationImageFilter< ImageType >;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput( reader->GetOutput() );

  const ImageType::SpacingType spacing( scalingFactor );
  filter->SetOutputSpacing( spacing );
  filter->ChangeSpacingOn();

  ImageType::PointType::VectorType translation;
  translation[0] = translationX;
  translation[1] = translationY;
  translation[2] = translationZ;
  ImageType::PointType origin = inputImage->GetOrigin();
  origin += translation;
  filter->SetOutputOrigin( origin );
  filter->ChangeOriginOn();

  itk::Versor< double > rotation;
  const double angleInRadians = rotationZ * vnl_math::pi / 180.0;
  rotation.SetRotationAroundZ( angleInRadians );
  const ImageType::DirectionType direction = inputImage->GetDirection();
  const ImageType::DirectionType newDirection
    = direction * rotation.GetMatrix();
  filter->SetOutputDirection( newDirection );
  filter->ChangeDirectionOn();

  try
    {
    filter->UpdateOutputInformation();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }
  std::cout << "**************************************" << std::endl;
  ImageType::ConstPointer output = filter->GetOutput();
  std::cout << "Changed image: " << output << std::endl;

  return EXIT_SUCCESS;
}
