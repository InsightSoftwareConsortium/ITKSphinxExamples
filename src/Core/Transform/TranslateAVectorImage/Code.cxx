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
#include "itkTranslationTransform.h"
#include "itkImageFileReader.h"
#include "itkResampleImageFilter.h"
#include "itkCovariantVector.h"
#include "itkNumericTraits.h"

int
main(int, char *[])
{
  using VectorType = itk::CovariantVector<double, 3>;
  using VectorImageType = itk::Image<VectorType, 2>;

  VectorImageType::Pointer image = VectorImageType::New();
  itk::Index<2>            start;
  start.Fill(0);

  itk::Size<2> size;
  size.Fill(10);

  itk::ImageRegion<2> region(start, size);
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(itk::NumericTraits<VectorType>::Zero);

  itk::TranslationTransform<double, 2>::Pointer          transform = itk::TranslationTransform<double, 2>::New();
  itk::TranslationTransform<double, 2>::OutputVectorType translation;
  translation[0] = 10;
  translation[1] = 20;
  transform->Translate(translation);

  using ResampleFilterType = itk::ResampleImageFilter<VectorImageType, VectorImageType>;
  ResampleFilterType::Pointer vectorResampleFilter = ResampleFilterType::New();
  vectorResampleFilter->SetInput(image);
  vectorResampleFilter->SetSize(image->GetLargestPossibleRegion().GetSize());
  vectorResampleFilter->SetTransform(transform);
  vectorResampleFilter->Update();

  return EXIT_SUCCESS;
}
