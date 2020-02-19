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
#include "itkImageFileWriter.h"
#include "itkImageRegionIterator.h"
#include "itkTIFFImageIO.h"
#include "itkRGBAPixel.h"

int
main(int argc, char * argv[])
{
  std::string outputFilename;
  if (argc > 1)
  {
    outputFilename = argv[1];
  }
  else
  {
    outputFilename = "test.tif";
  }

  using PixelType = itk::RGBAPixel<unsigned char>;
  using ImageType = itk::Image<PixelType, 2>;

  ImageType::RegionType region;
  ImageType::IndexType  start;
  start[0] = 0;
  start[1] = 0;

  ImageType::SizeType size;
  size[0] = 200;
  size[1] = 300;

  region.SetSize(size);
  region.SetIndex(start);

  ImageType::Pointer image = ImageType::New();
  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    ImageType::PixelType pixel = imageIterator.Get();

    if (imageIterator.GetIndex()[0] > 100)
    {
      pixel.SetRed(0);
      pixel.SetGreen(255);
      pixel.SetBlue(0);
      // pixel.SetAlpha(255); // invisible
      pixel.SetAlpha(122);
    }
    else
    {
      pixel.SetRed(255);
      pixel.SetGreen(0);
      pixel.SetBlue(0);
      pixel.SetAlpha(static_cast<unsigned char>(0.5 * 255));
    }
    imageIterator.Set(pixel);

    ++imageIterator;
  }

  using WriterType = itk::ImageFileWriter<ImageType>;
  using TIFFIOType = itk::TIFFImageIO;
  WriterType::Pointer writer = WriterType::New();
  TIFFIOType::Pointer tiffIO = TIFFIOType::New();
  tiffIO->SetPixelType(itk::IOPixelEnum::RGBA);
  writer->SetFileName(outputFilename);
  writer->SetInput(image);
  writer->SetImageIO(tiffIO);
  writer->Update();

  return EXIT_SUCCESS;
}
