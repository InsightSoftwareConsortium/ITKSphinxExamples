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

#include <iostream>
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkLabelImageGaussianInterpolateImageFunction.h"
#include "itkNearestNeighborInterpolateImageFunction.h"
#include "itkResampleImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 6)
  {
    std::cerr << "Usage: " << argv[0]
              << " inputImageFile spacingFraction sigmaFraction outputImageFileLabelImageInterpolator "
                 "outputImageFileNearestNeighborInterpolator"
              << std::endl;

    return EXIT_FAILURE;
  }
  const char * const inputImageFile = argv[1];
  const double       spacingFraction = std::stod(argv[2]);
  const double       sigmaFraction = std::stod(argv[3]);
  const char * const outputImageFileLabelImageInterpolator = argv[4];
  const char * const outputImageFileNearestNeighborInterpolator = argv[5];

  constexpr unsigned int Dimension = 2;
  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(inputImageFile);

  using ResampleFilterType = itk::ResampleImageFilter<ImageType, ImageType>;
  auto resizeFilter = ResampleFilterType::New();
  resizeFilter->SetInput(input);

  //     Compute and set the output size
  //
  //     The computation must be so that the following holds:
  //
  //     new width         old x spacing
  //     ----------   =   ---------------
  //     old width         new x spacing
  //
  //
  //     new height         old y spacing
  //    ------------  =   ---------------
  //     old height         new y spacing
  //
  //     So either we specify new height and width and compute new spacings
  //     or we specify new spacing and compute new height and width
  //     and computations that follows need to be modified a little (as it is

  const ImageType::SpacingType inputSpacing{ input->GetSpacing() };
  ImageType::SpacingType       outputSpacing;
  for (unsigned int dim = 0; dim < Dimension; ++dim)
  {
    outputSpacing[dim] = inputSpacing[dim] * spacingFraction;
  }
  resizeFilter->SetOutputSpacing(outputSpacing);

  const ImageType::RegionType inputRegion{ input->GetLargestPossibleRegion() };
  const ImageType::SizeType   inputSize{ inputRegion.GetSize() };
  ImageType::SizeType         outputSize;
  for (unsigned int dim = 0; dim < Dimension; ++dim)
  {
    outputSize[dim] = inputSize[dim] * inputSpacing[dim] / spacingFraction;
  }
  resizeFilter->SetSize(outputSize);

  using GaussianInterpolatorType = itk::LabelImageGaussianInterpolateImageFunction<ImageType, double>;
  auto                                gaussianInterpolator = GaussianInterpolatorType::New();
  GaussianInterpolatorType::ArrayType sigma;
  for (unsigned int dim = 0; dim < Dimension; ++dim)
  {
    sigma[dim] = outputSpacing[dim] * sigmaFraction;
  }
  gaussianInterpolator->SetSigma(sigma);
  gaussianInterpolator->SetAlpha(3.0);
  resizeFilter->SetInterpolator(gaussianInterpolator);

  try
  {
    itk::WriteImage(resizeFilter->GetOutput(), outputImageFileLabelImageInterpolator, true); // compress
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  using NearestNeighborInterpolatorType = itk::NearestNeighborInterpolateImageFunction<ImageType, double>;
  auto nearestNeighborInterpolator = NearestNeighborInterpolatorType::New();
  resizeFilter->SetInterpolator(nearestNeighborInterpolator);

  try
  {
    itk::WriteImage(resizeFilter->GetOutput(), outputImageFileNearestNeighborInterpolator, true); // compress
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
