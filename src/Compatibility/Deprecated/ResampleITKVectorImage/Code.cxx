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
#include "itkResampleImageFilter.h"
#include "itkVectorImage.h"

int
main(int, char *[])
{
  using VectorImageType = itk::VectorImage<double, 2>;

  VectorImageType::Pointer image = VectorImageType::New();
  itk::Index<2>            start;
  start.Fill(0);

  itk::Size<2> size;
  size.Fill(10);

  itk::ImageRegion<2> region(start, size);
  image->SetRegions(region);
  image->SetNumberOfComponentsPerPixel(3);
  image->Allocate();
  // image->FillBuffer(itk::NumericTraits<VectorImageType::InternalPixelType>::Zero);

  using ResampleFilterType = itk::ResampleImageFilter<VectorImageType, VectorImageType>;
  ResampleFilterType::Pointer vectorResampleFilter = ResampleFilterType::New();
  vectorResampleFilter->SetInput(image);
  vectorResampleFilter->Update();

  return EXIT_SUCCESS;
}
