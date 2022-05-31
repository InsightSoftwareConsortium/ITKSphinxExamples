/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
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

int
main(int argc, char * argv[])
{
  if (argc != 5)
  {
    std::cerr << "Usage: " << std::endl;
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
  using FloatImageType = itk::Image<FloatPixelType, Dimension>;

  const auto input = itk::ReadImage<FloatImageType>(inputFileName);

  using UnsignedCharPixelType = unsigned char;
  using UnsignedCharImageType = itk::Image<UnsignedCharPixelType, Dimension>;

  // Some FFT filter implementations, like VNL's, need the image size to be a
  // multiple of small prime numbers.
  using PadFilterType = itk::WrapPadImageFilter<FloatImageType, FloatImageType>;
  auto padFilter = PadFilterType::New();
  padFilter->SetInput(input);
  PadFilterType::SizeType padding;
  // Input size is [48, 62, 42].  Pad to [48, 64, 48].
  padding[0] = 0;
  padding[1] = 2;
  padding[2] = 6;
  padFilter->SetPadUpperBound(padding);

  using FFTType = itk::ForwardFFTImageFilter<FloatImageType>;
  auto fftFilter = FFTType::New();
  fftFilter->SetInput(padFilter->GetOutput());

  using FFTOutputImageType = FFTType::OutputImageType;

  // Extract the real part
  using RealFilterType = itk::ComplexToRealImageFilter<FFTOutputImageType, FloatImageType>;
  auto realFilter = RealFilterType::New();
  realFilter->SetInput(fftFilter->GetOutput());

  using RescaleFilterType = itk::RescaleIntensityImageFilter<FloatImageType, UnsignedCharImageType>;
  auto realRescaleFilter = RescaleFilterType::New();
  realRescaleFilter->SetInput(realFilter->GetOutput());
  realRescaleFilter->SetOutputMinimum(itk::NumericTraits<UnsignedCharPixelType>::min());
  realRescaleFilter->SetOutputMaximum(itk::NumericTraits<UnsignedCharPixelType>::max());

  try
  {
    itk::WriteImage(realRescaleFilter->GetOutput(), realFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  // Extract the imaginary part
  using ImaginaryFilterType = itk::ComplexToImaginaryImageFilter<FFTOutputImageType, FloatImageType>;
  auto imaginaryFilter = ImaginaryFilterType::New();
  imaginaryFilter->SetInput(fftFilter->GetOutput());

  auto imaginaryRescaleFilter = RescaleFilterType::New();
  imaginaryRescaleFilter->SetInput(imaginaryFilter->GetOutput());
  imaginaryRescaleFilter->SetOutputMinimum(itk::NumericTraits<UnsignedCharPixelType>::min());
  imaginaryRescaleFilter->SetOutputMaximum(itk::NumericTraits<UnsignedCharPixelType>::max());

  try
  {
    itk::WriteImage(imaginaryRescaleFilter->GetOutput(), imaginaryFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  // Compute the magnitude
  using ModulusFilterType = itk::ComplexToModulusImageFilter<FFTOutputImageType, FloatImageType>;
  auto modulusFilter = ModulusFilterType::New();
  modulusFilter->SetInput(fftFilter->GetOutput());

  auto magnitudeRescaleFilter = RescaleFilterType::New();
  magnitudeRescaleFilter->SetInput(modulusFilter->GetOutput());
  magnitudeRescaleFilter->SetOutputMinimum(itk::NumericTraits<UnsignedCharPixelType>::min());
  magnitudeRescaleFilter->SetOutputMaximum(itk::NumericTraits<UnsignedCharPixelType>::max());

  try
  {
    itk::WriteImage(magnitudeRescaleFilter->GetOutput(), modulusFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
