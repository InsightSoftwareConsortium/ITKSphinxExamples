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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkWrapPadImageFilter.h"
#include "itkForwardFFTImageFilter.h"
#include "itkGaussianImageSource.h"
#include "itkFFTShiftImageFilter.h"
#include "itkMultiplyImageFilter.h"
#include "itkInverseFFTImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << " [Sigma]";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];
  double       sigmaValue = 0.5;
  if (argc > 3)
  {
    sigmaValue = std::stod(argv[3]);
  }

  constexpr unsigned int Dimension = 3;

  using PixelType = float;
  using RealImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<RealImageType>(inputFileName);

  // Some FFT filter implementations, like VNL's, need the image size to be a
  // multiple of small prime numbers.
  using PadFilterType = itk::WrapPadImageFilter<RealImageType, RealImageType>;
  auto padFilter = PadFilterType::New();
  padFilter->SetInput(input);
  PadFilterType::SizeType padding;
  // Input size is [48, 62, 42].  Pad to [48, 64, 48].
  padding[0] = 0;
  padding[1] = 2;
  padding[2] = 6;
  padFilter->SetPadUpperBound(padding);

  using ForwardFFTFilterType = itk::ForwardFFTImageFilter<RealImageType>;
  using ComplexImageType = ForwardFFTFilterType::OutputImageType;
  auto forwardFFTFilter = ForwardFFTFilterType::New();
  forwardFFTFilter->SetInput(padFilter->GetOutput());

  try
  {
    forwardFFTFilter->UpdateOutputInformation();
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  // A Gaussian is used here to create a low-pass filter.
  using GaussianSourceType = itk::GaussianImageSource<RealImageType>;
  auto gaussianSource = GaussianSourceType::New();
  gaussianSource->SetNormalized(true);
  ComplexImageType::ConstPointer        transformedInput = forwardFFTFilter->GetOutput();
  const ComplexImageType::RegionType    inputRegion(transformedInput->GetLargestPossibleRegion());
  const ComplexImageType::SizeType      inputSize = inputRegion.GetSize();
  const ComplexImageType::SpacingType   inputSpacing = transformedInput->GetSpacing();
  const ComplexImageType::PointType     inputOrigin = transformedInput->GetOrigin();
  const ComplexImageType::DirectionType inputDirection = transformedInput->GetDirection();
  gaussianSource->SetSize(inputSize);
  gaussianSource->SetSpacing(inputSpacing);
  gaussianSource->SetOrigin(inputOrigin);
  gaussianSource->SetDirection(inputDirection);
  GaussianSourceType::ArrayType sigma;
  GaussianSourceType::PointType mean;
  sigma.Fill(sigmaValue);
  for (unsigned int ii = 0; ii < Dimension; ++ii)
  {
    const double halfLength = inputSize[ii] * inputSpacing[ii] / 2.0;
    sigma[ii] *= halfLength;
    mean[ii] = inputOrigin[ii] + halfLength;
  }
  mean = inputDirection * mean;
  gaussianSource->SetSigma(sigma);
  gaussianSource->SetMean(mean);

  using FFTShiftFilterType = itk::FFTShiftImageFilter<RealImageType, RealImageType>;
  auto fftShiftFilter = FFTShiftFilterType::New();
  fftShiftFilter->SetInput(gaussianSource->GetOutput());

  using MultiplyFilterType = itk::MultiplyImageFilter<ComplexImageType, RealImageType, ComplexImageType>;
  auto multiplyFilter = MultiplyFilterType::New();
  multiplyFilter->SetInput1(forwardFFTFilter->GetOutput());
  multiplyFilter->SetInput2(fftShiftFilter->GetOutput());

  using InverseFilterType = itk::InverseFFTImageFilter<ComplexImageType, RealImageType>;
  auto inverseFFTFilter = InverseFilterType::New();
  inverseFFTFilter->SetInput(multiplyFilter->GetOutput());

  try
  {
    itk::WriteImage(inverseFFTFilter->GetOutput(), outputFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
