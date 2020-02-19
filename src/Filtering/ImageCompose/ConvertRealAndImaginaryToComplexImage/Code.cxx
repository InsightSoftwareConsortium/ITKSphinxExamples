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

#if ITK_VERSION_MAJOR < 4
#  include "itkRealAndImaginaryToComplexImageFilter.h"
#else
#  include "itkComposeImageFilter.h"
#endif

#include <complex>

int
main(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  using ImageType = itk::Image<unsigned char, 2>;
  using ComplexImageType = itk::Image<std::complex<float>, 2>;

  ImageType::Pointer realImage = ImageType::New();
  ImageType::Pointer imaginaryImage = ImageType::New();

#if ITK_VERSION_MAJOR < 4
  using RealAndImaginaryToComplexImageFilterType =
    itk::RealAndImaginaryToComplexImageFilter<ImageType, ComplexImageType>;
#else
  using RealAndImaginaryToComplexImageFilterType = itk::ComposeImageFilter<ImageType, ComplexImageType>;
#endif
  RealAndImaginaryToComplexImageFilterType::Pointer realAndImaginaryToComplexImageFilter =
    RealAndImaginaryToComplexImageFilterType::New();
  realAndImaginaryToComplexImageFilter->SetInput1(realImage);
  realAndImaginaryToComplexImageFilter->SetInput2(imaginaryImage);
  realAndImaginaryToComplexImageFilter->Update();

  ComplexImageType * output = realAndImaginaryToComplexImageFilter->GetOutput();
  output->Print(std::cout);

  return EXIT_SUCCESS;
}
