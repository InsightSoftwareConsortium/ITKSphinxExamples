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
#include "itkSimpleFilterWatcher.h"
#include "itkAndImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkImageFileWriter.h"

using ImageType = itk::Image<unsigned char, 2>;
static void
CreateImage1(ImageType::Pointer image);
static void
CreateImage2(ImageType::Pointer image);

int
main(int, char *[])
{
  ImageType::Pointer image1 = ImageType::New();
  CreateImage1(image1);

  using WriterType = itk::ImageFileWriter<ImageType>;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName("input1.png");
  writer->SetInput(image1);
  writer->Update();

  ImageType::Pointer image2 = ImageType::New();
  CreateImage2(image2);

  writer->SetFileName("input2.png");
  writer->SetInput(image2);
  writer->Update();

  using AndImageFilterType = itk::AndImageFilter<ImageType>;

  AndImageFilterType::Pointer andFilter = AndImageFilterType::New();
  andFilter->SetInput(0, image1);
  andFilter->SetInput(1, image2);
  andFilter->Update();

  writer->SetFileName("output.png");
  writer->SetInput(andFilter->GetOutput());
  writer->Update();

  return EXIT_SUCCESS;
}

void
CreateImage1(ImageType::Pointer image)
{
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(100);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] < 70)
    {
      imageIterator.Set(255);
    }
    else
    {
      imageIterator.Set(0);
    }

    ++imageIterator;
  }
}

void
CreateImage2(ImageType::Pointer image)
{
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(100);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] > 30)
    {
      imageIterator.Set(255);
    }
    else
    {
      imageIterator.Set(0);
    }

    ++imageIterator;
  }
}
