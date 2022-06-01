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
#include "itkFFTNormalizedCorrelationImageFilter.h"
#include "itkRegionOfInterestImageFilter.h"
#include "itkImageKernelOperator.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkImageFileWriter.h"
#include "itkMinimumMaximumImageCalculator.h"

#include <iostream>
#include <string>

namespace
{
using ImageType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;
} // namespace

// using UnsignedCharImageType = itk::Image<unsigned char, 2>;

static void
CreateImage(ImageType::Pointer image, const itk::Index<2> & cornerOfSquare);

int
main()
{
  itk::Index<2> offset;
  offset[0] = 5;
  offset[1] = 6;

  auto          fixedImage = ImageType::New();
  itk::Index<2> cornerOfFixedSquare;
  cornerOfFixedSquare[0] = 3;
  cornerOfFixedSquare[1] = 8;
  CreateImage(fixedImage, cornerOfFixedSquare);
  itk::WriteImage(fixedImage.GetPointer(), "fixedImage.png");

  auto          movingImage = ImageType::New();
  itk::Index<2> cornerOfMovingSquare;
  cornerOfMovingSquare[0] = cornerOfFixedSquare[0] + offset[0];
  cornerOfMovingSquare[1] = cornerOfFixedSquare[1] + offset[1];
  CreateImage(movingImage, cornerOfMovingSquare);
  itk::WriteImage(movingImage.GetPointer(), "movingImage.png");

  // Perform normalized correlation
  using CorrelationFilterType = itk::FFTNormalizedCorrelationImageFilter<ImageType, FloatImageType>;
  auto correlationFilter = CorrelationFilterType::New();
  correlationFilter->SetFixedImage(fixedImage);
  correlationFilter->SetMovingImage(movingImage);
  correlationFilter->Update();

  itk::WriteImage(correlationFilter->GetOutput(), "correlation.mha");

  using RescaleFilterType = itk::RescaleIntensityImageFilter<FloatImageType, ImageType>;
  auto rescaleFilter = RescaleFilterType::New();
  rescaleFilter->SetInput(correlationFilter->GetOutput());
  rescaleFilter->SetOutputMinimum(0);
  rescaleFilter->SetOutputMaximum(255);
  rescaleFilter->Update();
  itk::WriteImage(rescaleFilter->GetOutput(), "correlation.png");

  using MinimumMaximumImageCalculatorType = itk::MinimumMaximumImageCalculator<FloatImageType>;
  MinimumMaximumImageCalculatorType::Pointer minimumMaximumImageCalculatorFilter =
    MinimumMaximumImageCalculatorType::New();
  minimumMaximumImageCalculatorFilter->SetImage(correlationFilter->GetOutput());
  minimumMaximumImageCalculatorFilter->Compute();

  itk::Index<2> maximumCorrelationPatchCenter = minimumMaximumImageCalculatorFilter->GetIndexOfMaximum();

  itk::Size<2> outputSize = correlationFilter->GetOutput()->GetLargestPossibleRegion().GetSize();

  itk::Index<2> maximumCorrelationPatchCenterFixed;
  maximumCorrelationPatchCenterFixed[0] = outputSize[0] / 2 - maximumCorrelationPatchCenter[0];
  maximumCorrelationPatchCenterFixed[1] = outputSize[1] / 2 - maximumCorrelationPatchCenter[1];

  std::cout << "Maximum location: " << maximumCorrelationPatchCenter << std::endl;
  std::cout << "Maximum location fixed: " << maximumCorrelationPatchCenterFixed
            << std::endl; // This is the value we expect!
  std::cout << "Maximum value: " << minimumMaximumImageCalculatorFilter->GetMaximum()
            << std::endl; // If the images can be perfectly aligned, the value is 1

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image, const itk::Index<2> & cornerOfSquare)
{
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(51);

  ImageType::RegionType region(start, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  ImageType::IndexValueType squareSize = 8;

  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] > cornerOfSquare[0] &&
        imageIterator.GetIndex()[0] < cornerOfSquare[0] + squareSize &&
        imageIterator.GetIndex()[1] > cornerOfSquare[1] && imageIterator.GetIndex()[1] < cornerOfSquare[1] + squareSize)
    {
      imageIterator.Set(255);
    }

    ++imageIterator;
  }
}
