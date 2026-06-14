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
#include "itkImageRegionIteratorWithIndex.h"
#include "itkImageFileReader.h"
#include "itkLabelImageToShapeLabelMapFilter.h"
#include "itkLabelStatisticsImageFilter.h"
#include "itkLabelToRGBImageFilter.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

using ImageType = itk::Image<unsigned int, 2>;
using RGBPixelType = itk::RGBPixel<unsigned char>;
using RGBImageType = itk::Image<RGBPixelType, 2>;

static void
CreateIntensityImage(ImageType::Pointer image);
static void
CreateLabelImage(ImageType::Pointer image);

int
main(int argc, char * argv[])
{
  auto labelImage = ImageType::New();
  auto intensityImage = ImageType::New();

  if (argc < 3)
  {
    // Create a label image that is 0 in the background and where the
    // objects are labeled.
    CreateLabelImage(labelImage);
    // Create an intensity image. Intensity statistics such as the
    // integrated intensity depend on an intensity image.
    CreateIntensityImage(intensityImage);
  }
  else
  {
    labelImage = itk::ReadImage<ImageType>(argv[1]);
    intensityImage = itk::ReadImage<ImageType>(argv[2]);
  }

  // Shape attributes (size, centroid, ellipsoid axes, elongation, ...).
  using LabelImageToShapeLabelMapFilterType = itk::LabelImageToShapeLabelMapFilter<ImageType>;
  auto shapeFilter = LabelImageToShapeLabelMapFilterType::New();
  shapeFilter->SetInput(labelImage);
  shapeFilter->Update();

  // Intensity statistics computed over each labeled region.
  using LabelStatisticsImageFilterType = itk::LabelStatisticsImageFilter<ImageType, ImageType>;
  auto statisticsFilter = LabelStatisticsImageFilterType::New();
  statisticsFilter->SetInput(intensityImage);
  statisticsFilter->SetLabelInput(labelImage);
  statisticsFilter->Update();

  auto labelMap = shapeFilter->GetOutput();
  std::cout << "Number of labels: " << labelMap->GetNumberOfLabelObjects() << std::endl;
  std::cout << std::endl;

  for (unsigned int n = 0; n < labelMap->GetNumberOfLabelObjects(); ++n)
  {
    const auto labelObject = labelMap->GetNthLabelObject(n);
    const auto labelValue = labelObject->GetLabel();

    std::cout << "\tLabel: " << static_cast<int>(labelValue) << std::endl;
    std::cout << "\tPhysical size: " << labelObject->GetPhysicalSize() << std::endl;
    std::cout << "\tNumber of pixels: " << labelObject->GetNumberOfPixels() << std::endl;
    std::cout << "\tCentroid: " << labelObject->GetCentroid() << std::endl;
    std::cout << "\tEquivalent ellipsoid diameter: " << labelObject->GetEquivalentEllipsoidDiameter() << std::endl;
    std::cout << "\tElongation: " << labelObject->GetElongation() << std::endl;
    std::cout << "\tFlatness: " << labelObject->GetFlatness() << std::endl;
    std::cout << "\tPrincipal axes: " << labelObject->GetPrincipalAxes() << std::endl;
    std::cout << "\tBounding box: " << labelObject->GetBoundingBox() << std::endl;

    if (statisticsFilter->HasLabel(labelValue))
    {
      std::cout << "\tIntegrated intensity: " << statisticsFilter->GetSum(labelValue) << std::endl;
      std::cout << "\tMean intensity: " << statisticsFilter->GetMean(labelValue) << std::endl;
    }

    std::cout << std::endl << std::endl;
  }

#ifdef ENABLE_QUICKVIEW
  using RGBFilterType = itk::LabelToRGBImageFilter<ImageType, RGBImageType>;
  auto rgbLabelImage = RGBFilterType::New();
  rgbLabelImage->SetInput(labelImage);

  QuickView viewer;
  viewer.ShareCameraOff();
  viewer.InterpolateOff();
  viewer.AddImage(rgbLabelImage->GetOutput(),
                  true,
                  argc > 2 ? itksys::SystemTools::GetFilenameName(argv[1]) : "Generated label image");
  viewer.AddImage(intensityImage.GetPointer(),
                  true,
                  argc > 2 ? itksys::SystemTools::GetFilenameName(argv[2]) : "Generated intensity image");
  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}

void
CreateIntensityImage(ImageType::Pointer image)
{
  // Create a random image.
  ImageType::IndexType start{};

  auto size = ImageType::SizeType::Filled(20);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);
  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIteratorWithIndex<ImageType> imageIterator(image, image->GetLargestPossibleRegion());
  // Make a random image
  // Create an unchanging seed.
  srand(1);
  while (!imageIterator.IsAtEnd())
  {
    int randomNumber = rand() % 255;
    imageIterator.Set(randomNumber);
    ++imageIterator;
  }
}

void
CreateLabelImage(ImageType::Pointer image)
{
  // Create a black image with labeled squares.
  ImageType::IndexType start{};

  auto size = ImageType::SizeType::Filled(20);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);
  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIteratorWithIndex<ImageType> imageIterator(image, image->GetLargestPossibleRegion());

  // Make a square
  while (!imageIterator.IsAtEnd())
  {
    if ((imageIterator.GetIndex()[0] > 5 && imageIterator.GetIndex()[0] < 10) &&
        (imageIterator.GetIndex()[1] > 5 && imageIterator.GetIndex()[1] < 10))
    {
      imageIterator.Set(85);
    }
    else if ((imageIterator.GetIndex()[0] > 11 && imageIterator.GetIndex()[0] < 17) &&
             (imageIterator.GetIndex()[1] > 11 && imageIterator.GetIndex()[1] < 17))
    {
      imageIterator.Set(127);
    }
    else if ((imageIterator.GetIndex()[0] > 11 && imageIterator.GetIndex()[0] < 17) &&
             (imageIterator.GetIndex()[1] > 1 && imageIterator.GetIndex()[1] < 5))
    {
      imageIterator.Set(191);
    }
    else
    {
      imageIterator.Set(0);
    }

    ++imageIterator;
  }
}
