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
#include "itkImageFileWriter.h"
#include "itkImage.h"
#include "itkVector.h"
#include "itkResampleImageFilter.h"
#include "itkLandmarkBasedTransformInitializer.h"
#include "itkRigid2DTransform.h"

constexpr unsigned int Dimension = 2;
using PixelType = unsigned char;
using ImageType = itk::Image<PixelType, Dimension>;

static void
CreateFixedImage(ImageType::Pointer image);
static void
CreateMovingImage(ImageType::Pointer image);

int
main(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  auto fixedImage = ImageType::New();
  CreateFixedImage(fixedImage);

  auto movingImage = ImageType::New();
  CreateMovingImage(movingImage);

  using TransformType = itk::Rigid2DTransform<double>;
  using LandmarkBasedTransformInitializerType =
    itk::LandmarkBasedTransformInitializer<TransformType, ImageType, ImageType>;

  LandmarkBasedTransformInitializerType::Pointer landmarkBasedTransformInitializer =
    LandmarkBasedTransformInitializerType::New();
  //  Create source and target landmarks.
  using LandmarkContainerType = LandmarkBasedTransformInitializerType::LandmarkPointContainer;
  using LandmarkPointType = LandmarkBasedTransformInitializerType::LandmarkPointType;

  LandmarkContainerType fixedLandmarks;
  LandmarkContainerType movingLandmarks;

  LandmarkPointType fixedPoint;
  LandmarkPointType movingPoint;

  fixedPoint[0] = 10;
  fixedPoint[1] = 10;
  movingPoint[0] = 50;
  movingPoint[1] = 50;
  fixedLandmarks.push_back(fixedPoint);
  movingLandmarks.push_back(movingPoint);

  fixedPoint[0] = 10;
  fixedPoint[1] = 20;
  movingPoint[0] = 50;
  movingPoint[1] = 60;
  fixedLandmarks.push_back(fixedPoint);
  movingLandmarks.push_back(movingPoint);

  fixedPoint[0] = 20;
  fixedPoint[1] = 10;
  movingPoint[0] = 60;
  movingPoint[1] = 50;
  fixedLandmarks.push_back(fixedPoint);
  movingLandmarks.push_back(movingPoint);

  fixedPoint[0] = 20;
  fixedPoint[1] = 20;
  movingPoint[0] = 60;
  movingPoint[1] = 60;
  fixedLandmarks.push_back(fixedPoint);
  movingLandmarks.push_back(movingPoint);

  landmarkBasedTransformInitializer->SetFixedLandmarks(fixedLandmarks);
  landmarkBasedTransformInitializer->SetMovingLandmarks(movingLandmarks);

  auto transform = TransformType::New();

  transform->SetIdentity();
  landmarkBasedTransformInitializer->SetTransform(transform);
  landmarkBasedTransformInitializer->InitializeTransform();

  using ResampleFilterType = itk::ResampleImageFilter<ImageType, ImageType, double>;
  auto resampleFilter = ResampleFilterType::New();
  resampleFilter->SetInput(movingImage);
  resampleFilter->SetTransform(transform);
  resampleFilter->SetUseReferenceImage(true);
  resampleFilter->SetReferenceImage(fixedImage);
  resampleFilter->SetDefaultPixelValue(200);

  itk::WriteImage(resampleFilter->GetOutput(), "output.png");

  return EXIT_SUCCESS;
}

void
CreateFixedImage(ImageType::Pointer image)
{
  // Create a black image with a white square
  ImageType::IndexType start{};

  auto size = ImageType::SizeType::Filled(100);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] > 10 && imageIterator.GetIndex()[0] < 20 && imageIterator.GetIndex()[1] > 10 &&
        imageIterator.GetIndex()[1] < 20)
    {
      imageIterator.Set(255);
    }
    ++imageIterator;
  }

  itk::WriteImage(image, "fixed.png");
}


void
CreateMovingImage(ImageType::Pointer image)
{
  // Create a black image with a white square
  ImageType::IndexType start{};

  auto size = ImageType::SizeType::Filled(100);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] > 50 && imageIterator.GetIndex()[0] < 60 && imageIterator.GetIndex()[1] > 50 &&
        imageIterator.GetIndex()[1] < 60)
    {
      imageIterator.Set(100);
    }
    ++imageIterator;
  }

  itk::WriteImage(image, "moving.png");
}
