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
#include "itkSpatialObjectToImageFilter.h"
#include "itkLineSpatialObject.h"
#include "itkLineSpatialObjectPoint.h"
#include "itkImageFileWriter.h"

int
main(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  using PixelType = unsigned char;
  constexpr unsigned int Dimension = 2;

  using ImageType = itk::Image<PixelType, Dimension>;

  using LineType = itk::LineSpatialObject<Dimension>;

  using SpatialObjectToImageFilterType = itk::SpatialObjectToImageFilter<LineType, ImageType>;


  // Create a list of points
  std::vector<LineType::LinePointType> points;
  for (unsigned int i = 0; i < 20; ++i)
  {
    LineType::LinePointType point;
    point.SetPositionInObjectSpace(10, i);

    LineType::LinePointType::CovariantVectorType normal;
    normal[0] = 0;
    normal[1] = 1;
    point.SetNormalInObjectSpace(normal, 0);
    points.push_back(point);
  }

  // Create a line from the list of points
  auto line = LineType::New();
  line->SetPoints(points);

  auto imageFilter = SpatialObjectToImageFilterType::New();
  auto size = itk::Size<2>::Filled(50);
  imageFilter->SetInsideValue(255); // white
  imageFilter->SetSize(size);
  imageFilter->SetInput(line);
  imageFilter->Update();

  itk::WriteImage(imageFilter->GetOutput(), "line.png");

  return EXIT_SUCCESS;
}
