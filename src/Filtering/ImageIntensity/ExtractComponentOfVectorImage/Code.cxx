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
#include "itkVectorImage.h"
#include "itkImageRegionIterator.h"
#include "itkMinimumMaximumImageCalculator.h"
#include "itkVectorIndexSelectionCastImageFilter.h"

using VectorImageType = itk::VectorImage<float, 2>;
using ScalarImageType = itk::Image<float, 2>;

static void
CreateImage(VectorImageType::Pointer image);

int
main()
{
  auto image = VectorImageType::New();
  CreateImage(image);

  using IndexSelectionType = itk::VectorIndexSelectionCastImageFilter<VectorImageType, ScalarImageType>;
  auto indexSelectionFilter = IndexSelectionType::New();
  indexSelectionFilter->SetIndex(0);
  indexSelectionFilter->SetInput(image);

  using ImageCalculatorFilterType = itk::MinimumMaximumImageCalculator<ScalarImageType>;
  auto imageCalculatorFilter = ImageCalculatorFilterType::New();
  imageCalculatorFilter->SetImage(indexSelectionFilter->GetOutput());
  imageCalculatorFilter->Compute();

  return EXIT_SUCCESS;
}

void
CreateImage(VectorImageType::Pointer image)
{
  VectorImageType::IndexType start;
  start.Fill(0);

  VectorImageType::SizeType size;
  size.Fill(2);

  VectorImageType::RegionType region(start, size);

  image->SetRegions(region);
  image->SetNumberOfComponentsPerPixel(3);
  image->Allocate();

  using VariableVectorType = itk::VariableLengthVector<double>;
  VariableVectorType variableLengthVector;
  variableLengthVector.SetSize(3);
  variableLengthVector[0] = 1.1;
  variableLengthVector[1] = 2.2;
  variableLengthVector[2] = 3.3;

  image->FillBuffer(variableLengthVector);
}
