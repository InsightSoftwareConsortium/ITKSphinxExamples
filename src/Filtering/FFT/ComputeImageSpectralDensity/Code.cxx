/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#include "itkWrapPadImageFilter.h"
#include "itkForwardFFTImageFilter.h"
#include "itkComplexToModulusImageFilter.h"
#include "itkIntensityWindowingImageFilter.h"
#include "itkFFTShiftImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  constexpr unsigned int Dimension = 3;

  using PixelType = float;
  using RealImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<RealImageType>(inputFileName);

  // Some FFT filter implementations, like VNL's, need the image size to be a
  // multiple of small prime numbers.
  using PadFilterType = itk::WrapPadImageFilter<RealImageType, RealImageType>;
  PadFilterType::Pointer padFilter = PadFilterType::New();
  padFilter->SetInput(input);
  PadFilterType::SizeType padding;
  // Input size is [48, 62, 42].  Pad to [48, 64, 48].
  padding[0] = 0;
  padding[1] = 2;
  padding[2] = 6;
  padFilter->SetPadUpperBound(padding);

  using ForwardFFTFilterType = itk::ForwardFFTImageFilter<RealImageType>;
  using ComplexImageType = ForwardFFTFilterType::OutputImageType;
  ForwardFFTFilterType::Pointer forwardFFTFilter = ForwardFFTFilterType::New();
  forwardFFTFilter->SetInput(padFilter->GetOutput());

  using ComplexToModulusFilterType = itk::ComplexToModulusImageFilter<ComplexImageType, RealImageType>;
  ComplexToModulusFilterType::Pointer complexToModulusFilter = ComplexToModulusFilterType::New();
  complexToModulusFilter->SetInput(forwardFFTFilter->GetOutput());

  // Window and shift the output for visualization.
  using OutputPixelType = unsigned short;
  using OutputImageType = itk::Image<OutputPixelType, Dimension>;
  using WindowingFilterType = itk::IntensityWindowingImageFilter<RealImageType, OutputImageType>;
  WindowingFilterType::Pointer windowingFilter = WindowingFilterType::New();
  windowingFilter->SetInput(complexToModulusFilter->GetOutput());
  windowingFilter->SetWindowMinimum(0);
  windowingFilter->SetWindowMaximum(20000);

  using FFTShiftFilterType = itk::FFTShiftImageFilter<OutputImageType, OutputImageType>;
  FFTShiftFilterType::Pointer fftShiftFilter = FFTShiftFilterType::New();
  fftShiftFilter->SetInput(windowingFilter->GetOutput());

  try
  {
    itk::WriteImage(fftShiftFilter->GetOutput(), outputFileName);
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
