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
#include "itkIdentityTransform.h"
#include "itkImageFileReader.h"
#include "itkVectorResampleImageFilter.h"
#include "itkVectorNearestNeighborInterpolateImageFunction.h"
#include "itkRGBPixel.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

using ImageType = itk::Image<itk::RGBPixel<unsigned char>, 2>;

static void
CreateImage(ImageType::Pointer image);

int
main(int argc, char * argv[])
{
  double factor = 2.0;

  // Create input image
  ImageType::Pointer input;
  if (argc < 2)
  {
    input = ImageType::New();
    CreateImage(input);
  }
  else
  {
    using ReaderType = itk::ImageFileReader<ImageType>;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    input = reader->GetOutput();
    if (argc > 2)
    {
      factor = std::stod(argv[2]);
    }
  }

  ImageType::SizeType inputSize = input->GetLargestPossibleRegion().GetSize();

  std::cout << "Input size: " << inputSize << std::endl;

  // Resize
  ImageType::SizeType outputSize;
  outputSize[0] = inputSize[0] * factor;
  outputSize[1] = inputSize[1] * factor;

  ImageType::SpacingType outputSpacing;
  outputSpacing[0] = input->GetSpacing()[0] * (static_cast<double>(inputSize[0]) / static_cast<double>(outputSize[0]));
  outputSpacing[1] = input->GetSpacing()[1] * (static_cast<double>(inputSize[1]) / static_cast<double>(outputSize[1]));

  using TransformType = itk::IdentityTransform<double, 2>;
  using ResampleImageFilterType = itk::VectorResampleImageFilter<ImageType, ImageType>;
  ResampleImageFilterType::Pointer resample = ResampleImageFilterType::New();
  resample->SetInput(input);
  resample->SetSize(outputSize);
  resample->SetOutputSpacing(outputSpacing);
  resample->SetTransform(TransformType::New());
  resample->UpdateLargestPossibleRegion();

  using NearestInterpolatorType = itk::VectorNearestNeighborInterpolateImageFunction<ImageType, double>;
  NearestInterpolatorType::Pointer nnInterpolator = NearestInterpolatorType::New();

  ResampleImageFilterType::Pointer resampleNN = ResampleImageFilterType::New();
  resampleNN->SetInput(input);
  resampleNN->SetSize(outputSize);
  resampleNN->SetOutputSpacing(outputSpacing);
  resampleNN->SetTransform(TransformType::New());
  resampleNN->SetInterpolator(nnInterpolator);
  resampleNN->UpdateLargestPossibleRegion();

  ImageType::Pointer output = resample->GetOutput();

  std::cout << "Output size: " << output->GetLargestPossibleRegion().GetSize() << std::endl;

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;

  viewer.AddRGBImage(input.GetPointer(), true, "Original");
  viewer.AddRGBImage(output.GetPointer(), true, "Resampled");

  viewer.AddRGBImage(resampleNN->GetOutput(), true, "Resampled NN");

  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  // Create a black image with 2 white regions

  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(200);

  ImageType::RegionType region(start, size);
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(itk::NumericTraits<ImageType::PixelType>::Zero);

  ImageType::PixelType pixel;
  pixel.SetRed(200);
  pixel.SetGreen(50);
  pixel.SetBlue(50);

  // Make a square
  for (unsigned int r = 20; r < 80; r++)
  {
    for (unsigned int c = 30; c < 100; c++)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, pixel);
    }
  }
}
