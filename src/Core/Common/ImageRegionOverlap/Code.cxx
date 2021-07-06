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

#include <cstdlib>
#include <cstdio>

#include "itkRGBPixel.h"
#include "itkImageRegionIterator.h"
#include "itkImageFileWriter.h"


int
main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << std::endl;
    std::cerr << " <OutputFileName>" << std::endl;

    return EXIT_FAILURE;
  }
  const char * out_file_name = argv[1];

  constexpr unsigned int Dimension = 2;
  using RGBPixelType = itk::RGBPixel<unsigned char>;
  using RGBImageType = itk::Image<RGBPixelType, Dimension>;
  using RegionType = RGBImageType::RegionType;
  using IndexType = RGBImageType::IndexType;
  using SizeType = RGBImageType::SizeType;
  using IteratorType = itk::ImageRegionIterator<RGBImageType>;


  IndexType index;
  index[0] = 0;
  index[1] = 0;

  SizeType size;
  size[0] = 100;
  size[1] = 100;

  RegionType region;
  region.SetIndex(index);
  region.SetSize(size);

  IndexType indexA;
  indexA[0] = 9;
  indexA[1] = 9;

  SizeType sizeA;
  sizeA[0] = 50;
  sizeA[1] = 50;

  RegionType regionA;
  regionA.SetIndex(indexA);
  regionA.SetSize(sizeA);

  IndexType indexB;
  indexB[0] = 39;
  indexB[1] = 39;

  SizeType sizeB;
  sizeB[0] = 50;
  sizeB[1] = 50;

  RegionType regionB;
  regionB.SetIndex(indexB);
  regionB.SetSize(sizeB);

  // Region C is the intersection of A and B
  // padded by 10 pixels.
  RegionType regionC = regionA;
  regionC.Crop(regionB);
  regionC.PadByRadius(10);

  RGBPixelType pix_black;
  pix_black.Fill(0);

  RGBPixelType pix_red;
  pix_red.Fill(0);
  pix_red[0] = 255;

  RGBPixelType pix_green;
  pix_green.Fill(0);
  pix_green[1] = 255;

  RGBPixelType pix_blue;
  pix_blue.Fill(0);
  pix_blue[2] = 255;

  // A black canvas
  RGBImageType::Pointer image = RGBImageType::New();
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(pix_black);

  // Paint region A red.
  IteratorType itA(image, regionA);
  itA.GoToBegin();
  while (!itA.IsAtEnd())
  {
    itA.Set(itA.Get() + pix_red);
    ++itA;
  }

  // Paint region B green.
  IteratorType itB(image, regionB);
  itB.GoToBegin();
  while (!itB.IsAtEnd())
  {
    itB.Set(itB.Get() + pix_green);
    ++itB;
  }

  // Paint region C blue.
  IteratorType itC(image, regionC);
  itC.GoToBegin();
  while (!itC.IsAtEnd())
  {
    itC.Set(itC.Get() + pix_blue);
    ++itC;
  }

  try
  {
    itk::WriteImage(image, out_file_name);
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
