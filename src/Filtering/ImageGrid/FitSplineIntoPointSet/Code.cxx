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
#include "itkBSplineScatteredDataPointSetToImageFilter.h"
#include "itkPointSet.h"
#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkImageFileWriter.h"

int
main()
{
  constexpr unsigned int ParametricDimension = 1;
  constexpr unsigned int DataDimension = 2;

  using DataType = itk::Vector<float, DataDimension>;

  using PointSetType = itk::PointSet<DataType, ParametricDimension>;

  auto pointSet = PointSetType::New();

  PointSetType::PointType param0, param1, param2;

  param0[0] = 0.0;
  DataType p0;
  p0[0] = 10.0;
  p0[1] = 10.0;

  pointSet->SetPoint(0, param0);
  pointSet->SetPointData(0, p0);

  param1[0] = 1.0;
  DataType p1;
  p1[0] = 80.0;
  p1[1] = 50.0;
  pointSet->SetPoint(1, param1);
  pointSet->SetPointData(1, p1);

  param2[0] = 2.0;
  DataType p2;
  p2[0] = 180.0;
  p2[1] = 180.0;
  pointSet->SetPoint(2, param2);
  pointSet->SetPointData(2, p2);

  using ImageType = itk::Image<DataType, ParametricDimension>;
  using SplineFilterType = itk::BSplineScatteredDataPointSetToImageFilter<PointSetType, ImageType>;
  auto splineFilter = SplineFilterType::New();

  int splineorder = 2; // complexity of the spline

  SplineFilterType::ArrayType ncontrol;
  ncontrol[0] = splineorder + 1;
  SplineFilterType::ArrayType closedim;
  closedim[0] = 0;

  ImageType::PointType parametricDomainOrigin;
  parametricDomainOrigin[0] = 0.0;

  ImageType::SpacingType parametricDomainSpacing;
  parametricDomainSpacing[0] = 0.0001; // this determines the sampling of the continuous B-spline object.

  ImageType::SizeType parametricDomainSize;
  parametricDomainSize[0] = 2.0 / parametricDomainSpacing[0] + 1;
  splineFilter->SetGenerateOutputImage(true); // the only reason to turn this off is if one only wants to use the
                                              // control point lattice for further processing
  splineFilter->SetInput(pointSet);
  splineFilter->SetSplineOrder(splineorder);
  splineFilter->SetNumberOfControlPoints(ncontrol);
  splineFilter->SetNumberOfLevels(3);
  splineFilter->SetCloseDimension(closedim);
  splineFilter->SetSize(parametricDomainSize);
  splineFilter->SetSpacing(parametricDomainSpacing);
  splineFilter->SetOrigin(parametricDomainOrigin);
  splineFilter->Update();

  // The output will consist of a 1-D image where each voxel contains the
  // (x,y,z) locations of the points
  using OutputImageType = itk::Image<unsigned char, 2>;
  auto                      outputImage = OutputImageType::New();
  OutputImageType::SizeType size;
  size.Fill(200);

  OutputImageType::IndexType start;
  start.Fill(0);

  OutputImageType::RegionType region(start, size);
  outputImage->SetRegions(region);
  outputImage->Allocate();
  outputImage->FillBuffer(0);

  for (unsigned int i = 0; i < splineFilter->GetOutput()->GetLargestPossibleRegion().GetSize()[0]; ++i)
  {
    ImageType::IndexType splineIndex;
    splineIndex[0] = i;

    DataType outputPixel = splineFilter->GetOutput()->GetPixel(splineIndex);

    OutputImageType::IndexType index;
    index[0] = outputPixel[0];
    index[1] = outputPixel[1];

    outputImage->SetPixel(index, 255);
  }

  itk::WriteImage(outputImage, "spline.png");

  return EXIT_SUCCESS;
};
