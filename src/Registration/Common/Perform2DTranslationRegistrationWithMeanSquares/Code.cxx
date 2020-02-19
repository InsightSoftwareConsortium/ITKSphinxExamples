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

#include "itkImageRegistrationMethodv4.h"
#include "itkTranslationTransform.h"
#include "itkMeanSquaresImageToImageMetricv4.h"
#include "itkRegularStepGradientDescentOptimizerv4.h"

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkResampleImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkSubtractImageFilter.h"


int
main(int argc, char * argv[])
{
  if (argc != 6)
  {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " fixedImageFile  movingImageFile ";
    std::cerr << "outputImagefile [differenceImageAfter]";
    std::cerr << "[differenceImageBefore]" << std::endl;
    return EXIT_FAILURE;
  }

  const char * fixedImageFile = argv[1];
  const char * movingImageFile = argv[2];
  const char * outputImageFile = argv[3];
  const char * differenceImageAfterFile = argv[4];
  const char * differenceImageBeforeFile = argv[5];

  constexpr unsigned int Dimension = 2;
  using PixelType = float;

  using FixedImageType = itk::Image<PixelType, Dimension>;
  using MovingImageType = itk::Image<PixelType, Dimension>;


  using FixedImageReaderType = itk::ImageFileReader<FixedImageType>;
  auto fixedImageReader = FixedImageReaderType::New();
  fixedImageReader->SetFileName(fixedImageFile);

  using MovingImageReaderType = itk::ImageFileReader<MovingImageType>;
  auto movingImageReader = MovingImageReaderType::New();
  movingImageReader->SetFileName(movingImageFile);


  using TransformType = itk::TranslationTransform<double, Dimension>;
  auto initialTransform = TransformType::New();

  using OptimizerType = itk::RegularStepGradientDescentOptimizerv4<double>;
  auto optimizer = OptimizerType::New();
  optimizer->SetLearningRate(4);
  optimizer->SetMinimumStepLength(0.001);
  optimizer->SetRelaxationFactor(0.5);
  optimizer->SetNumberOfIterations(200);

  using MetricType = itk::MeanSquaresImageToImageMetricv4<FixedImageType, MovingImageType>;
  auto metric = MetricType::New();

  using RegistrationType = itk::ImageRegistrationMethodv4<FixedImageType, MovingImageType>;
  auto registration = RegistrationType::New();
  registration->SetInitialTransform(initialTransform);
  registration->SetMetric(metric);
  registration->SetOptimizer(optimizer);
  registration->SetFixedImage(fixedImageReader->GetOutput());
  registration->SetMovingImage(movingImageReader->GetOutput());

  auto                          movingInitialTransform = TransformType::New();
  TransformType::ParametersType initialParameters(movingInitialTransform->GetNumberOfParameters());
  initialParameters[0] = 0.0;
  initialParameters[1] = 0.0;
  movingInitialTransform->SetParameters(initialParameters);
  registration->SetMovingInitialTransform(movingInitialTransform);

  auto identityTransform = TransformType::New();
  identityTransform->SetIdentity();
  registration->SetFixedInitialTransform(identityTransform);

  constexpr unsigned int numberOfLevels = 1;
  registration->SetNumberOfLevels(numberOfLevels);

  RegistrationType::ShrinkFactorsArrayType shrinkFactorsPerLevel;
  shrinkFactorsPerLevel.SetSize(1);
  shrinkFactorsPerLevel[0] = 1;
  registration->SetShrinkFactorsPerLevel(shrinkFactorsPerLevel);

  RegistrationType::SmoothingSigmasArrayType smoothingSigmasPerLevel;
  smoothingSigmasPerLevel.SetSize(1);
  smoothingSigmasPerLevel[0] = 0;
  registration->SetSmoothingSigmasPerLevel(smoothingSigmasPerLevel);

  try
  {
    registration->Update();
    std::cout << "Optimizer stop condition: " << registration->GetOptimizer()->GetStopConditionDescription()
              << std::endl;
  }
  catch (itk::ExceptionObject & err)
  {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
  }

  auto transform = registration->GetTransform();
  auto finalParameters = transform->GetParameters();
  auto translationAlongX = finalParameters[0];
  auto translationAlongY = finalParameters[1];

  auto numberOfIterations = optimizer->GetCurrentIteration();

  auto bestValue = optimizer->GetValue();

  std::cout << "Result = " << std::endl;
  std::cout << " Translation X = " << translationAlongX << std::endl;
  std::cout << " Translation Y = " << translationAlongY << std::endl;
  std::cout << " Iterations    = " << numberOfIterations << std::endl;
  std::cout << " Metric value  = " << bestValue << std::endl;

  using CompositeTransformType = itk::CompositeTransform<double, Dimension>;
  auto outputCompositeTransform = CompositeTransformType::New();
  outputCompositeTransform->AddTransform(movingInitialTransform);
  outputCompositeTransform->AddTransform(registration->GetModifiableTransform());

  using ResampleFilterType = itk::ResampleImageFilter<MovingImageType, FixedImageType>;
  auto resampler = ResampleFilterType::New();
  resampler->SetInput(movingImageReader->GetOutput());
  resampler->SetTransform(outputCompositeTransform);
  auto fixedImage = fixedImageReader->GetOutput();
  resampler->SetUseReferenceImage(true);
  resampler->SetReferenceImage(fixedImage);
  resampler->SetDefaultPixelValue(100);

  using OutputPixelType = unsigned char;
  using OutputImageType = itk::Image<OutputPixelType, Dimension>;

  using CastFilterType = itk::CastImageFilter<FixedImageType, OutputImageType>;
  auto caster = CastFilterType::New();
  caster->SetInput(resampler->GetOutput());

  using WriterType = itk::ImageFileWriter<OutputImageType>;
  auto writer = WriterType::New();
  writer->SetFileName(outputImageFile);
  writer->SetInput(caster->GetOutput());
  writer->Update();

  using DifferenceFilterType = itk::SubtractImageFilter<FixedImageType, FixedImageType, FixedImageType>;
  auto difference = DifferenceFilterType::New();
  difference->SetInput1(fixedImageReader->GetOutput());
  difference->SetInput2(resampler->GetOutput());

  using RescalerType = itk::RescaleIntensityImageFilter<FixedImageType, OutputImageType>;
  auto intensityRescaler = RescalerType::New();
  intensityRescaler->SetInput(difference->GetOutput());
  intensityRescaler->SetOutputMinimum(itk::NumericTraits<OutputPixelType>::min());
  intensityRescaler->SetOutputMaximum(itk::NumericTraits<OutputPixelType>::max());

  resampler->SetDefaultPixelValue(1);

  writer->SetInput(intensityRescaler->GetOutput());
  writer->SetFileName(differenceImageAfterFile);
  writer->Update();

  resampler->SetTransform(identityTransform);
  writer->SetFileName(differenceImageBeforeFile);
  writer->Update();

  return EXIT_SUCCESS;
}
