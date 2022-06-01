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
#include "itkImageFileReader.h"
#include "itkMeanSquaresImageToImageMetric.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkTranslationTransform.h"

int
main(int argc, char * argv[])
{
  using ImageType = itk::Image<double, 2>;

  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " imageFile1 imageFile2" << std::endl;
    return EXIT_FAILURE;
  }

  ImageType::Pointer fixedImage = itk::ReadImage<ImageType>(argv[1]);
  ImageType::Pointer movingImage = itk::ReadImage<ImageType>(argv[2]);

  using MetricType = itk::MeanSquaresImageToImageMetric<ImageType, ImageType>;
  using InterpolatorType = itk::LinearInterpolateImageFunction<ImageType, double>;
  using TransformType = itk::TranslationTransform<double, 2>;

  auto metric = MetricType::New();
  auto transform = TransformType::New();

  auto interpolator = InterpolatorType::New();
  interpolator->SetInputImage(fixedImage);

  metric->SetFixedImage(fixedImage);
  metric->SetMovingImage(movingImage);
  metric->SetFixedImageRegion(fixedImage->GetLargestPossibleRegion());
  metric->SetTransform(transform);
  metric->SetInterpolator(interpolator);

  TransformType::ParametersType params(transform->GetNumberOfParameters());
  params.Fill(0.0);

  metric->Initialize();
  for (double x = -10.0; x <= 10.0; x += 5.0)
  {
    params(0) = x;
    for (double y = -10.0; y <= 10.0; y += 5.0)
    {
      params(1) = y;
      std::cout << params << ": " << metric->GetValue(params) << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
