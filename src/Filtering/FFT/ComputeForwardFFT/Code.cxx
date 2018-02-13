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
#include "itkWrapPadImageFilter.h"
#include "itkForwardFFTImageFilter.h"
#include "itkComplexToRealImageFilter.h"
#include "itkComplexToImaginaryImageFilter.h"
#include "itkComplexToModulusImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int main( int argc, char* argv[] )
{
  if( argc != 5 )
    {
    std::cerr << "Usage: "<< std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <Real filename> <Imaginary filename> <Modulus filename>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * realFileName = argv[2];
  const char * imaginaryFileName = argv[3];
  const char * modulusFileName = argv[4];

  constexpr unsigned int Dimension = 3;

  using FloatPixelType = float;
  using FloatImageType = itk::Image< FloatPixelType, Dimension >;

  using ReaderType = itk::ImageFileReader< FloatImageType >;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputFileName );

  using UnsignedCharPixelType = unsigned char;
  using UnsignedCharImageType = itk::Image< UnsignedCharPixelType, Dimension >;

  // Some FFT filter implementations, like VNL's, need the image size to be a
  // multiple of small prime numbers.
  using PadFilterType = itk::WrapPadImageFilter< FloatImageType, FloatImageType >;
  PadFilterType::Pointer padFilter = PadFilterType::New();
  padFilter->SetInput( reader->GetOutput() );
  PadFilterType::SizeType padding;
  // Input size is [48, 62, 42].  Pad to [48, 64, 48].
  padding[0] = 0;
  padding[1] = 2;
  padding[2] = 6;
  padFilter->SetPadUpperBound( padding );

  using FFTType = itk::ForwardFFTImageFilter< FloatImageType >;
  FFTType::Pointer fftFilter = FFTType::New();
  fftFilter->SetInput( padFilter->GetOutput() );

  using FFTOutputImageType = FFTType::OutputImageType;

  // Extract the real part
  using RealFilterType = itk::ComplexToRealImageFilter< FFTOutputImageType, FloatImageType>;
  RealFilterType::Pointer realFilter = RealFilterType::New();
  realFilter->SetInput(fftFilter->GetOutput());

  using RescaleFilterType = itk::RescaleIntensityImageFilter< FloatImageType, UnsignedCharImageType >;
  RescaleFilterType::Pointer realRescaleFilter = RescaleFilterType::New();
  realRescaleFilter->SetInput(realFilter->GetOutput());
  realRescaleFilter->SetOutputMinimum( itk::NumericTraits< UnsignedCharPixelType >::min() );
  realRescaleFilter->SetOutputMaximum( itk::NumericTraits< UnsignedCharPixelType >::max() );

  using WriterType = itk::ImageFileWriter< UnsignedCharImageType >;
  WriterType::Pointer realWriter = WriterType::New();
  realWriter->SetFileName( realFileName );
  realWriter->SetInput( realRescaleFilter->GetOutput() );
  try
    {
    realWriter->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  // Extract the imaginary part
  using ImaginaryFilterType = itk::ComplexToImaginaryImageFilter< FFTOutputImageType, FloatImageType>;
  ImaginaryFilterType::Pointer imaginaryFilter = ImaginaryFilterType::New();
  imaginaryFilter->SetInput(fftFilter->GetOutput());

  RescaleFilterType::Pointer imaginaryRescaleFilter = RescaleFilterType::New();
  imaginaryRescaleFilter->SetInput(imaginaryFilter->GetOutput());
  imaginaryRescaleFilter->SetOutputMinimum( itk::NumericTraits< UnsignedCharPixelType >::min() );
  imaginaryRescaleFilter->SetOutputMaximum( itk::NumericTraits< UnsignedCharPixelType >::max() );

  WriterType::Pointer complexWriter = WriterType::New();
  complexWriter->SetFileName( imaginaryFileName );
  complexWriter->SetInput( imaginaryRescaleFilter->GetOutput() );
  try
    {
    complexWriter->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  // Compute the magnitude
  using ModulusFilterType = itk::ComplexToModulusImageFilter< FFTOutputImageType, FloatImageType>;
  ModulusFilterType::Pointer modulusFilter = ModulusFilterType::New();
  modulusFilter->SetInput(fftFilter->GetOutput());

  RescaleFilterType::Pointer magnitudeRescaleFilter = RescaleFilterType::New();
  magnitudeRescaleFilter->SetInput(modulusFilter->GetOutput());
  magnitudeRescaleFilter->SetOutputMinimum( itk::NumericTraits< UnsignedCharPixelType >::min() );
  magnitudeRescaleFilter->SetOutputMaximum( itk::NumericTraits< UnsignedCharPixelType >::max() );

  WriterType::Pointer magnitudeWriter = WriterType::New();
  magnitudeWriter->SetFileName( modulusFileName );
  magnitudeWriter->SetInput( magnitudeRescaleFilter->GetOutput() );
  try
    {
    magnitudeWriter->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
