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
// Maximum value is inf??

#include "itkImage.h"
#include "itkNormalizedCorrelationImageFilter.h"
#include "itkRegionOfInterestImageFilter.h"
#include "itkImageKernelOperator.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkImageFileWriter.h"
#include "itkMinimumMaximumImageCalculator.h"

#include <iostream>
#include <string>

using ImageType = itk::Image<unsigned char, 2>;
using MaskType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;

void
CreateMask(MaskType * const mask);
void
CreateImage(ImageType * const image);
void
CreateImageOfSquare(ImageType * const image, const itk::Index<2> & cornerOfSquare);

int
main(int, char *[])
{
  // Setup mask
  MaskType::Pointer mask = MaskType::New();
  CreateMask(mask);

  itk::WriteImage(mask.GetPointer(), "mask.png");

  // Setup image1
  ImageType::Pointer image1 = ImageType::New();
  itk::Index<2>      cornerOfSquare1;
  cornerOfSquare1[0] = 3;
  cornerOfSquare1[1] = 8;
  CreateImageOfSquare(image1, cornerOfSquare1);
  itk::WriteImage(image1.GetPointer(), "image1.png");

  // Setup image2
  itk::Index<2> offset;
  offset[0] = 20;
  offset[1] = 6;

  ImageType::Pointer image2 = ImageType::New();
  itk::Index<2>      cornerOfSquare2;
  cornerOfSquare2[0] = cornerOfSquare1[0] + offset[0];
  cornerOfSquare2[1] = cornerOfSquare1[1] + offset[1];
  CreateImageOfSquare(image2, cornerOfSquare2);

  itk::WriteImage(image2.GetPointer(), "image2.png");

  // Create a kernel from an image
  itk::ImageKernelOperator<unsigned char> kernelOperator;
  kernelOperator.SetImageKernel(image1);

  // The radius of the kernel must be the radius of the patch, NOT the size of the patch
  itk::Size<2> radius;
  radius[0] = image1->GetLargestPossibleRegion().GetSize()[0] / 2;
  radius[1] = image1->GetLargestPossibleRegion().GetSize()[1] / 2;

  if (radius[0] % 2 == 0 || radius[1] % 2 == 0)
  {
    std::cerr << "Input must have odd dimensions!" << std::endl;
    return EXIT_FAILURE;
  }

  kernelOperator.CreateToRadius(radius);

  // Perform normalized correlation
  // <input type, mask type, output type>
  using CorrelationFilterType =
    itk::NormalizedCorrelationImageFilter<ImageType, MaskType, FloatImageType, unsigned char>;
  CorrelationFilterType::Pointer correlationFilter = CorrelationFilterType::New();
  correlationFilter->SetInput(image2);
  correlationFilter->SetMaskImage(mask);
  correlationFilter->SetTemplate(kernelOperator);
  correlationFilter->Update();

  itk::WriteImage(correlationFilter->GetOutput(), "correlation.mha");

  using RescaleFilterType = itk::RescaleIntensityImageFilter<FloatImageType, ImageType>;
  RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
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

  // This is the value we expect!
  std::cout << "Maximum location fixed: " << maximumCorrelationPatchCenter - radius << std::endl;

  // If the images can be perfectly aligned, the value is 1
  std::cout << "Maximum value: " << minimumMaximumImageCalculatorFilter->GetMaximum() << std::endl;

  return EXIT_SUCCESS;
}

void
CreateMask(MaskType * const mask)
{
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(51);

  ImageType::RegionType region(start, size);

  mask->SetRegions(region);
  mask->Allocate();
  mask->FillBuffer(255); // Make the whole mask "valid"

  // unsigned int squareSize = 8;
  unsigned int squareSize = 3;

  itk::Index<2> cornerOfSquare = { { 3, 8 } };

  // Remove pixels from the mask in a small square. The correlationw will not be computed at these pixels.
  itk::ImageRegionIterator<MaskType> maskIterator(mask, region);

  while (!maskIterator.IsAtEnd())
  {
    if (maskIterator.GetIndex()[0] > cornerOfSquare[0] && maskIterator.GetIndex()[0] < cornerOfSquare[0] + squareSize &&
        maskIterator.GetIndex()[1] > cornerOfSquare[1] && maskIterator.GetIndex()[1] < cornerOfSquare[1] + squareSize)
    {
      maskIterator.Set(0);
    }

    ++maskIterator;
  }
}

void
CreateImage(ImageType * const image)
{
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(51);

  ImageType::RegionType region(start, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);
}

void
CreateImageOfSquare(ImageType * const image, const itk::Index<2> & cornerOfSquare)
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

  unsigned int squareSize = 8;

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
