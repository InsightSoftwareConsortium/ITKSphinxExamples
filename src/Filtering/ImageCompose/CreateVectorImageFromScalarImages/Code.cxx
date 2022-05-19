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
#include "itkComposeImageFilter.h"
#include "itkVectorImage.h"

namespace
{
using VectorImageType = itk::VectorImage<unsigned char, 2>;
using ScalarImageType = itk::Image<unsigned char, 2>;
} // namespace

static void
CreateImage(ScalarImageType::Pointer image);

int
main()
{
  ScalarImageType::Pointer image0 = ScalarImageType::New();
  CreateImage(image0);

  ScalarImageType::Pointer image1 = ScalarImageType::New();
  CreateImage(image1);

  ScalarImageType::Pointer image2 = ScalarImageType::New();
  CreateImage(image2);

  using ImageToVectorImageFilterType = itk::ComposeImageFilter<ScalarImageType>;
  ImageToVectorImageFilterType::Pointer imageToVectorImageFilter = ImageToVectorImageFilterType::New();
  imageToVectorImageFilter->SetInput(0, image0);
  imageToVectorImageFilter->SetInput(1, image1);
  imageToVectorImageFilter->SetInput(2, image2);
  imageToVectorImageFilter->Update();

  VectorImageType::Pointer vectorImage = imageToVectorImageFilter->GetOutput();

  return EXIT_SUCCESS;
}

void
CreateImage(ScalarImageType::Pointer image)
{
  ScalarImageType::IndexType start;
  start.Fill(0);

  ScalarImageType::SizeType size;
  size.Fill(100);

  ScalarImageType::RegionType region(start, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);
}
