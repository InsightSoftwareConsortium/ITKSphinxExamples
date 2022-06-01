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
#include "itkScaleTransform.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkResampleImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: " << argv[0] << " inputFile outputFile" << std::endl;
  }

  using PixelType = unsigned char;
  constexpr unsigned int ImageDimension = 2;
  using ImageType = itk::Image<PixelType, ImageDimension>;
  auto image = itk::ReadImage<ImageType>(argv[1]);

  using MetricValueType = double;
  using TransformType = itk::ScaleTransform<MetricValueType, 2>;
  auto                      scaleTransform = TransformType::New();
  itk::FixedArray<float, 2> scale;
  scale[0] = 1.5; // newWidth/oldWidth
  scale[1] = 1.5;
  scaleTransform->SetScale(scale);

  itk::Point<float, 2> center;
  center[0] = image->GetLargestPossibleRegion().GetSize()[0] / 2;
  center[1] = image->GetLargestPossibleRegion().GetSize()[1] / 2;

  scaleTransform->SetCenter(center);

  using ResampleImageFilterType = itk::ResampleImageFilter<ImageType, ImageType, MetricValueType>;
  auto resampleFilter = ResampleImageFilterType::New();
  resampleFilter->SetTransform(scaleTransform);
  resampleFilter->SetInput(image);
  resampleFilter->SetSize(image->GetLargestPossibleRegion().GetSize());
  resampleFilter->Update();

  itk::WriteImage(resampleFilter->GetOutput(), argv[2]);

  return EXIT_SUCCESS;
}
