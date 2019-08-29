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
#include "itkSpatialObjectToImageFilter.h"
#include "itkContourSpatialObject.h"
#include "itkContourSpatialObjectPoint.h"
#include "itkImageFileWriter.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

int
main(int /*argc*/, char * /*argv*/[])
{
  using PixelType = unsigned char;
  constexpr unsigned int Dimension = 2;

  using ImageType = itk::Image<PixelType, Dimension>;

  using ContourType = itk::ContourSpatialObject<Dimension>;

  using SpatialObjectToImageFilterType = itk::SpatialObjectToImageFilter<ContourType, ImageType>;


  // Create a list of points
  ContourType::ControlPointListType points;

  // Add some points
  ContourType::ControlPointType point;
  point.SetPositionInObjectSpace(0, 0);
  points.push_back(point);
  point.SetPositionInObjectSpace(0, 30);
  points.push_back(point);
  point.SetPositionInObjectSpace(30, 30);
  points.push_back(point);
  point.SetPositionInObjectSpace(0, 0);
  points.push_back(point);

  // Create a contour from the list of points
  ContourType::Pointer contour = ContourType::New();
  contour->SetControlPoints(points);

  SpatialObjectToImageFilterType::Pointer imageFilter = SpatialObjectToImageFilterType::New();
  itk::Size<2>                            size;
  size.Fill(50);
  imageFilter->SetInsideValue(255); // white
  imageFilter->SetSize(size);
  imageFilter->SetInput(contour);
  imageFilter->Update();

  using WriterType = itk::ImageFileWriter<ImageType>;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName("contour.png");
  writer->SetInput(imageFilter->GetOutput());
  writer->Update();

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(imageFilter->GetOutput());
  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}
