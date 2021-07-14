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

#include "itkAdaptiveHistogramEqualizationImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int
main(int argc, char * argv[])
{
  if (argc < 6)
  {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << argv[0] << " inputImageFile outputImageFile alpha beta radius" << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(argv[1]);

  using AdaptiveHistogramEqualizationImageFilterType = itk::AdaptiveHistogramEqualizationImageFilter<ImageType>;
  AdaptiveHistogramEqualizationImageFilterType::Pointer adaptiveHistogramEqualizationImageFilter =
    AdaptiveHistogramEqualizationImageFilterType::New();

  float alpha = std::stod(argv[3]);
  adaptiveHistogramEqualizationImageFilter->SetAlpha(alpha);

  float beta = std::stod(argv[4]);
  adaptiveHistogramEqualizationImageFilter->SetBeta(beta);

  int                                                         radiusSize = std::stoi(argv[5]);
  AdaptiveHistogramEqualizationImageFilterType::ImageSizeType radius;
  radius.Fill(radiusSize);
  adaptiveHistogramEqualizationImageFilter->SetRadius(radius);

  adaptiveHistogramEqualizationImageFilter->SetInput(input);

  adaptiveHistogramEqualizationImageFilter->Update();

  itk::WriteImage(adaptiveHistogramEqualizationImageFilter->GetOutput(), argv[2]);

  return EXIT_SUCCESS;
}
