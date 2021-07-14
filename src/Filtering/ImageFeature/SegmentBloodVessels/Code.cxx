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

#include "itkHessian3DToVesselnessMeasureImageFilter.h"
#include "itkHessianRecursiveGaussianImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int
main(int argc, char * argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: <InputImage> <OutputImage> [Sigma] [Alpha1] [Alpha2]" << std::endl;
    return EXIT_FAILURE;
  }
  const char * inputImage = argv[1];
  const char * outputImage = argv[2];
  double       sigma = 1.0;
  if (argc > 3)
  {
    sigma = std::atof(argv[3]);
  }
  double alpha1 = 0.5;
  if (argc > 4)
  {
    alpha1 = std::atof(argv[4]);
  }
  double alpha2 = 2.0;
  if (argc > 5)
  {
    alpha2 = std::atof(argv[5]);
  }

  constexpr unsigned int Dimension = 3;
  using PixelType = float;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(inputImage);

  using HessianFilterType = itk::HessianRecursiveGaussianImageFilter<ImageType>;
  HessianFilterType::Pointer hessianFilter = HessianFilterType::New();
  hessianFilter->SetInput(input);
  hessianFilter->SetSigma(sigma);

  using VesselnessMeasureFilterType = itk::Hessian3DToVesselnessMeasureImageFilter<PixelType>;
  VesselnessMeasureFilterType::Pointer vesselnessFilter = VesselnessMeasureFilterType::New();
  vesselnessFilter->SetInput(hessianFilter->GetOutput());
  vesselnessFilter->SetAlpha1(alpha1);
  vesselnessFilter->SetAlpha2(alpha2);

  try
  {
    itk::WriteImage(vesselnessFilter->GetOutput(), outputImage);
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
