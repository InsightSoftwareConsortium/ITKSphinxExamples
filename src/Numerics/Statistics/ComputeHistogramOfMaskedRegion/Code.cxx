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
#include "itkMaskedImageToHistogramFilter.h"
#include "itkImage.h"
#include "itkImageFileWriter.h"
#include "itkRGBPixel.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkImageRegionIterator.h"
#include "itkRescaleIntensityImageFilter.h"

using RGBPixelType = itk::RGBPixel<unsigned char>;
using RGBImageType = itk::Image<RGBPixelType, 2>;

using UnsignedCharImageType = itk::Image<unsigned char, 2>;

static void
            CreateImage(RGBImageType::Pointer image);
static void CreateHalfMask(itk::ImageRegion<2>, UnsignedCharImageType::Pointer mask);

int
main(int, char *[])
{
  constexpr unsigned int MeasurementVectorSize = 3; // RGB

  RGBImageType::Pointer image = RGBImageType::New();
  CreateImage(image);

  UnsignedCharImageType::Pointer mask = UnsignedCharImageType::New();
  CreateHalfMask(image->GetLargestPossibleRegion(), mask);

  using HistogramFilterType = itk::Statistics::MaskedImageToHistogramFilter<RGBImageType, UnsignedCharImageType>;
  using HistogramMeasurementVectorType = HistogramFilterType::HistogramMeasurementVectorType;
  using HistogramSizeType = HistogramFilterType::HistogramSizeType;
  using HistogramType = HistogramFilterType::HistogramType;

  HistogramFilterType::Pointer histogramFilter = HistogramFilterType::New();
  histogramFilter->SetInput(image);
  histogramFilter->SetMaskImage(mask);
  histogramFilter->SetAutoMinimumMaximum(true);

  HistogramSizeType histogramSize(MeasurementVectorSize);

  histogramSize[0] = 4; // number of bins for the Red   channel
  histogramSize[1] = 4; // number of bins for the Green channel
  histogramSize[2] = 4; // number of bins for the Blue  channel

  histogramFilter->SetHistogramSize(histogramSize);
  histogramFilter->SetMarginalScale(10); // Required (could this be set in the filter?)
  histogramFilter->Update();

  const HistogramType * histogram = histogramFilter->GetOutput();

  HistogramType::ConstIterator histogramIterator = histogram->Begin();

  // std::string filename = "/home/doriad/histogram.txt";
  // std::ofstream fout(filename.c_str());

  while (histogramIterator != histogram->End())
  {
    // std::cout << "Index = " << histogramIterator.GetMeasurementVector() << "Frequency = " <<
    // histogramIterator.GetFrequency() << std::endl; std::cout << "Index = " << histogramIterator.GetIndex() <<
    // "Frequency = " << histogramIterator.GetFrequency() << std::endl; fout << "Index = " <<
    // histogram->GetIndex(histogramItr.GetMeasurementVector()) << "Frequency = " << histogramItr.GetFrequency() <<
    // std::endl;
    ++histogramIterator;
  }
  // fout.close();

  HistogramType::MeasurementVectorType mv(3);
  mv[0] = 255;
  mv[1] = 0;
  mv[2] = 0;
  std::cout << "Frequency = " << histogram->GetFrequency(histogram->GetIndex(mv)) << std::endl;
  return EXIT_SUCCESS;
}

void
CreateImage(RGBImageType::Pointer image)
{
  // Create a black image with a red square and a green square.
  // This should produce a histogram with very strong spikes.
  RGBImageType::SizeType size;
  size[0] = 3;
  size[1] = 3;

  RGBImageType::IndexType start;
  start[0] = 0;
  start[1] = 0;

  RGBImageType::RegionType region;
  region.SetIndex(start);
  region.SetSize(size);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIteratorWithIndex<RGBImageType> iterator(image, image->GetLargestPossibleRegion());
  iterator.GoToBegin();

  RGBPixelType redPixel;
  redPixel.SetRed(255);
  redPixel.SetGreen(0);
  redPixel.SetBlue(0);

  RGBPixelType blackPixel;
  blackPixel.SetRed(0);
  blackPixel.SetGreen(0);
  blackPixel.SetBlue(0);

  itk::ImageRegionIterator<RGBImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    imageIterator.Set(blackPixel);
    ++imageIterator;
  }

  RGBImageType::IndexType index;
  index[0] = 0;
  index[1] = 0;
  image->SetPixel(index, redPixel);

  index[0] = 1;
  index[1] = 0;
  image->SetPixel(index, redPixel);
}

void CreateHalfMask(itk::ImageRegion<2> region, UnsignedCharImageType::Pointer mask)
{
  mask->SetRegions(region);
  mask->Allocate();
  mask->FillBuffer(0);

  itk::Size<2> regionSize = region.GetSize();

  itk::ImageRegionIterator<UnsignedCharImageType> imageIterator(mask, region);

  // Make the left half of the mask white and the right half black
  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] > regionSize[0] / 2)
    {
      imageIterator.Set(0);
    }
    else
    {
      imageIterator.Set(1);
    }

    ++imageIterator;
  }

  using RescaleFilterType = itk::RescaleIntensityImageFilter<UnsignedCharImageType, UnsignedCharImageType>;
  RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
  rescaleFilter->SetInput(mask);
  rescaleFilter->Update();

  itk::WriteImage(rescaleFilter->GetOutput(), "mask.png");
}
