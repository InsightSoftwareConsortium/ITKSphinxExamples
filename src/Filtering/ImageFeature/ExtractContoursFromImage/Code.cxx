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
/*
#include "itkImage.h"
#include "itkImageFileWriter.h"
#include "itkSimpleContourExtractorImageFilter.h"
#include "itkImageRegionIterator.h"

using UnsignedCharImageType = itk::Image<unsigned char, 2>;

static void CreateImage(UnsignedCharImageType::Pointer image);

int main()
{
  auto image = UnsignedCharImageType::New();
  CreateImage(image);

  using SimpleContourExtractorImageFilterType = itk::SimpleContourExtractorImageFilter <UnsignedCharImageType, UnsignedCharImageType>;
  SimpleContourExtractorImageFilterType::Pointer contourFilter
          = SimpleContourExtractorImageFilterType::New();
  contourFilter->SetInput(image);
  contourFilter->Update();

  using WriterType = itk::ImageFileWriter< UnsignedCharImageType  >;
  auto writer = WriterType::New();
  writer->SetFileName("output.png");
  writer->SetInput(contourFilter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}

void CreateImage(UnsignedCharImageType::Pointer image)
{
  // Create an image
  itk::Index<2> start;
  start.Fill(0);

  itk::Size<2> size;
  size.Fill(100);

  itk::ImageRegion<2> region(start,size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  // Create a line pixels
  for(unsigned int i = 40; i < 60; ++i)
    {
    itk::Index<2> pixel;
    pixel.Fill(i);
    image->SetPixel(pixel, 255);
    }

  // Create another line of pixels
  for(unsigned int i = 10; i < 20; ++i)
    {
    itk::Index<2> pixel;
    pixel[0] = 10;
    pixel[1] = i;
    image->SetPixel(pixel, 255);
    }

  using WriterType = itk::ImageFileWriter< UnsignedCharImageType  >;
  auto writer = WriterType::New();
  writer->SetFileName("input.png");
  writer->SetInput(image);
  writer->Update();
}
