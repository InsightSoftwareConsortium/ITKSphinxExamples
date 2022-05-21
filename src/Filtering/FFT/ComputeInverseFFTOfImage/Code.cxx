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
#include "itkImage.h"
#include "itkForwardFFTImageFilter.h"
#include "itkInverseFFTImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkImageFileReader.h"
#include "itkCastImageFilter.h"
#include "itkImageFileWriter.h"

using FloatImageType = itk::Image<float, 2>;

static void
CreateImage(FloatImageType * const image);

int
main(int argc, char * argv[])
{
  FloatImageType::Pointer image;
  // Verify input
  if (argc < 2)
  {
    image = FloatImageType::New();
    CreateImage(image);
    // std::cerr << "Required: filename" << std::endl;
    // return EXIT_FAILURE;
  }
  else
  {
    image = itk::ReadImage<FloatImageType>(argv[1]);
  }

  // Define some types
  using UnsignedCharImageType = itk::Image<unsigned char, 2>;

  // Compute the FFT
  using FFTType = itk::ForwardFFTImageFilter<FloatImageType>;
  auto fftFilter = FFTType::New();
  fftFilter->SetInput(image);
  fftFilter->Update();

  // Compute the IFFT
  // using IFFTType = itk::InverseFFTImageFilter<FFTType::OutputImageType, UnsignedCharImageType>; // This does not work
  // - output type seems to need to be float, but it is just an error, not a concept check error...
  using IFFTType = itk::InverseFFTImageFilter<FFTType::OutputImageType, FloatImageType>;
  auto ifftFilter = IFFTType::New();
  ifftFilter->SetInput(fftFilter->GetOutput());
  ifftFilter->Update();

  using CastFilterType = itk::CastImageFilter<FloatImageType, UnsignedCharImageType>;
  auto castFilter = CastFilterType::New();
  castFilter->SetInput(ifftFilter->GetOutput());
  castFilter->Update();

  itk::WriteImage(castFilter->GetOutput(), "ifft.png");

  return EXIT_SUCCESS;
}

void
CreateImage(FloatImageType * const image)
{
  itk::Index<2> corner = { { 0, 0 } };

  itk::Size<2> size = { { 200, 200 } };

  itk::ImageRegion<2> region(corner, size);

  image->SetRegions(region);
  image->Allocate();

  // Make a square
  for (FloatImageType::IndexValueType r = 40; r < 100; ++r)
  {
    for (FloatImageType::IndexValueType c = 40; c < 100; ++c)
    {
      FloatImageType::IndexType pixelIndex = { { r, c } };

      image->SetPixel(pixelIndex, 100);
    }
  }
}
