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
#include "itkScaleTransform.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkResampleImageFilter.h"

using ImageType = itk::Image<unsigned char, 2>;

static void
CreateImage(ImageType::Pointer image);

int
main(int, char *[])
{
  ImageType::Pointer image = ImageType::New();
  CreateImage(image);

  using WriterType = itk::ImageFileWriter<ImageType>;
  WriterType::Pointer inputWriter = WriterType::New();
  inputWriter->SetFileName("input.png");
  inputWriter->SetInput(image);
  inputWriter->Update();

  // using TransformType = itk::ScaleTransform<float, 2>; // If you want to use float here, you must use:
  // using ResampleImageFilterType = itk::ResampleImageFilter<ImageType, ImageType, float>; later.
  using TransformType = itk::ScaleTransform<double, 2>;
  TransformType::Pointer    scaleTransform = TransformType::New();
  itk::FixedArray<float, 2> scale;
  scale[0] = 1.5; // newWidth/oldWidth
  scale[1] = 1.5;
  scaleTransform->SetScale(scale);

  itk::Point<float, 2> center;
  center[0] = image->GetLargestPossibleRegion().GetSize()[0] / 2;
  center[1] = image->GetLargestPossibleRegion().GetSize()[1] / 2;

  scaleTransform->SetCenter(center);

  using ResampleImageFilterType = itk::ResampleImageFilter<ImageType, ImageType>;
  ResampleImageFilterType::Pointer resampleFilter = ResampleImageFilterType::New();
  resampleFilter->SetTransform(scaleTransform);
  resampleFilter->SetInput(image);
  resampleFilter->SetSize(image->GetLargestPossibleRegion().GetSize());
  resampleFilter->Update();

  WriterType::Pointer outputWriter = WriterType::New();
  outputWriter->SetFileName("output.png");
  outputWriter->SetInput(resampleFilter->GetOutput());
  outputWriter->Update();

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  itk::Index<2> start;
  start.Fill(0);

  itk::Size<2> size;
  size.Fill(101);

  ImageType::RegionType region(start, size);
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  // Make a white square
  for (unsigned int r = 40; r < 60; r++)
  {
    for (unsigned int c = 40; c < 60; c++)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 255);
    }
  }

  itk::ImageRegionIterator<ImageType> imageIterator(image, image->GetLargestPossibleRegion());

  // Draw a white border
  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] == 0 ||
        imageIterator.GetIndex()[0] == static_cast<int>(image->GetLargestPossibleRegion().GetSize()[0]) - 1 ||
        imageIterator.GetIndex()[1] == 0 ||
        imageIterator.GetIndex()[1] == static_cast<int>(image->GetLargestPossibleRegion().GetSize()[1]) - 1)
    {
      imageIterator.Set(255);
    }
    ++imageIterator;
  }
}
