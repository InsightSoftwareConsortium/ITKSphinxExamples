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
#include "itkImageRegistrationMethod.h"
#include "itkAffineTransform.h"
#include "itkMutualInformationImageToImageMetric.h"
#include "itkGradientDescentOptimizer.h"
#include "itkNormalizeImageFilter.h"
#include "itkDiscreteGaussianImageFilter.h"
#include "itkResampleImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkCheckerBoardImageFilter.h"
#include "itkEllipseSpatialObject.h"
#include "itkSpatialObjectToImageFilter.h"
#include "itkImageFileWriter.h"
#include "itkImageFileReader.h"

constexpr unsigned int Dimension = 2;
using PixelType = unsigned char;

using ImageType = itk::Image<PixelType, Dimension>;

int
main(int argc, char * argv[])
{

  if (argc < 4)
  {
    std::cout << "Usage: " << argv[0] << " imageFile1 imageFile2 outputFile" << std::endl;
    return EXIT_FAILURE;
  }
  ImageType::Pointer fixedImage = itk::ReadImage<ImageType>(argv[1]);

  ImageType::Pointer movingImage = itk::ReadImage<ImageType>(argv[2]);

  // We use floats internally
  using InternalImageType = itk::Image<float, Dimension>;

  // Normalize the images
  using NormalizeFilterType = itk::NormalizeImageFilter<ImageType, InternalImageType>;

  auto fixedNormalizer = NormalizeFilterType::New();
  auto movingNormalizer = NormalizeFilterType::New();

  fixedNormalizer->SetInput(fixedImage);
  movingNormalizer->SetInput(movingImage);

  // Smooth the normalized images
  using GaussianFilterType = itk::DiscreteGaussianImageFilter<InternalImageType, InternalImageType>;

  auto fixedSmoother = GaussianFilterType::New();
  auto movingSmoother = GaussianFilterType::New();

  fixedSmoother->SetVariance(2.0);
  movingSmoother->SetVariance(2.0);

  fixedSmoother->SetInput(fixedNormalizer->GetOutput());
  movingSmoother->SetInput(movingNormalizer->GetOutput());

  using TransformType = itk::AffineTransform<double, Dimension>;
  using OptimizerType = itk::GradientDescentOptimizer;
  using InterpolatorType = itk::LinearInterpolateImageFunction<InternalImageType, double>;
  using RegistrationType = itk::ImageRegistrationMethod<InternalImageType, InternalImageType>;
  using MetricType = itk::MutualInformationImageToImageMetric<InternalImageType, InternalImageType>;

  auto transform = TransformType::New();
  auto optimizer = OptimizerType::New();
  auto interpolator = InterpolatorType::New();
  auto registration = RegistrationType::New();

  registration->SetOptimizer(optimizer);
  registration->SetTransform(transform);
  registration->SetInterpolator(interpolator);

  auto metric = MetricType::New();
  registration->SetMetric(metric);

  //  The metric requires a number of parameters to be selected, including
  //  the standard deviation of the Gaussian kernel for the fixed image
  //  density estimate, the standard deviation of the kernel for the moving
  //  image density and the number of samples use to compute the densities
  //  and entropy values. Details on the concepts behind the computation of
  //  the metric can be found in Section
  //  \ref{sec:MutualInformationMetric}.  Experience has
  //  shown that a kernel standard deviation of $0.4$ works well for images
  //  which have been normalized to a mean of zero and unit variance.  We
  //  will follow this empirical rule in this example.

  metric->SetFixedImageStandardDeviation(5.0);
  metric->SetMovingImageStandardDeviation(5.0);

  registration->SetFixedImage(fixedSmoother->GetOutput());
  registration->SetMovingImage(movingSmoother->GetOutput());

  fixedNormalizer->Update();
  ImageType::RegionType fixedImageRegion = fixedNormalizer->GetOutput()->GetBufferedRegion();
  registration->SetFixedImageRegion(fixedImageRegion);

  using ParametersType = RegistrationType::ParametersType;
  ParametersType initialParameters(transform->GetNumberOfParameters());

  // rotation matrix (identity)
  initialParameters[0] = 1.0; // R(0,0)
  initialParameters[1] = 0.0; // R(0,1)
  initialParameters[2] = 0.0; // R(1,0)
  initialParameters[3] = 1.0; // R(1,1)

  // translation vector
  initialParameters[4] = 0.0;
  initialParameters[5] = 0.0;

  registration->SetInitialTransformParameters(initialParameters);

  //  Software Guide : BeginLatex
  //
  //  We should now define the number of spatial samples to be considered in
  //  the metric computation. Note that we were forced to postpone this setting
  //  until we had done the preprocessing of the images because the number of
  //  samples is usually defined as a fraction of the total number of pixels in
  //  the fixed image.
  //
  //  The number of spatial samples can usually be as low as $1\%$ of the total
  //  number of pixels in the fixed image. Increasing the number of samples
  //  improves the smoothness of the metric from one iteration to another and
  //  therefore helps when this metric is used in conjunction with optimizers
  //  that rely of the continuity of the metric values. The trade-off, of
  //  course, is that a larger number of samples result in longer computation
  //  times per every evaluation of the metric.
  //
  //  It has been demonstrated empirically that the number of samples is not a
  //  critical parameter for the registration process. When you start fine
  //  tuning your own registration process, you should start using high values
  //  of number of samples, for example in the range of $20\%$ to $50\%$ of the
  //  number of pixels in the fixed image. Once you have succeeded to register
  //  your images you can then reduce the number of samples progressively until
  //  you find a good compromise on the time it takes to compute one evaluation
  //  of the Metric. Note that it is not useful to have very fast evaluations
  //  of the Metric if the noise in their values results in more iterations
  //  being required by the optimizer to converge. You must then study the
  //  behavior of the metric values as the iterations progress.

  const unsigned int numberOfPixels = fixedImageRegion.GetNumberOfPixels();

  const auto numberOfSamples = static_cast<unsigned int>(numberOfPixels * 0.01);

  metric->SetNumberOfSpatialSamples(numberOfSamples);

  // For consistent results when regression testing.
  metric->ReinitializeSeed(121212);

  // Note that large values of the learning rate will make the optimizer
  // unstable. Small values, on the other hand, may result in the optimizer
  // needing too many iterations in order to walk to the extrema of the cost
  // function. The easy way of fine tuning this parameter is to start with
  // small values, probably in the range of $\{5.0,10.0\}$. Once the other
  // registration parameters have been tuned for producing convergence, you
  // may want to revisit the learning rate and start increasing its value until
  // you observe that the optimization becomes unstable.  The ideal value for
  // this parameter is the one that results in a minimum number of iterations
  // while still keeping a stable path on the parametric space of the
  // optimization. Keep in mind that this parameter is a multiplicative factor
  // applied on the gradient of the Metric. Therefore, its effect on the
  // optimizer step length is proportional to the Metric values themselves.
  // Metrics with large values will require you to use smaller values for the
  // learning rate in order to maintain a similar optimizer behavior.
  optimizer->SetLearningRate(1.0);

  // Note that the only stop condition for the v3 GradientDescentOptimizer class
  // is that the maximum number of iterations is reached.
  // For the option to exit early on convergence use GradientDescentOptimizerv4
  // with an accompanying v4 metric class.
  optimizer->SetNumberOfIterations(200);
  optimizer->MaximizeOn(); // We want to maximize mutual information (the default of the optimizer is to minimize)

  auto scales = optimizer->GetScales();

  // Let optimizer take
  // large steps along translation parameters,
  // moderate steps along rotational parameters,
  // and small steps along scale parameters
  scales.SetSize(6);
  scales.SetElement(0, 100);
  scales.SetElement(1, 0.5);
  scales.SetElement(2, 0.5);
  scales.SetElement(3, 100);
  scales.SetElement(4, 0.0001);
  scales.SetElement(5, 0.0001);

  optimizer->SetScales(scales);

  try
  {
    registration->Update();
    std::cout << "Optimizer stop condition: " << registration->GetOptimizer()->GetStopConditionDescription()
              << std::endl;
  }
  catch (const itk::ExceptionObject & err)
  {
    std::cout << "ExceptionObject caught !" << std::endl;
    std::cout << err << std::endl;
    return EXIT_FAILURE;
  }

  ParametersType finalParameters = registration->GetLastTransformParameters();

  std::cout << "Final Parameters: " << finalParameters << std::endl;

  unsigned int numberOfIterations = optimizer->GetCurrentIteration();

  double bestValue = optimizer->GetValue();

  // Print out results
  std::cout << std::endl;
  std::cout << "Result = " << std::endl;
  std::cout << " Iterations    = " << numberOfIterations << std::endl;
  std::cout << " Metric value  = " << bestValue << std::endl;
  std::cout << " Numb. Samples = " << numberOfSamples << std::endl;

  using ResampleFilterType = itk::ResampleImageFilter<ImageType, ImageType>;

  auto finalTransform = TransformType::New();

  finalTransform->SetParameters(finalParameters);
  finalTransform->SetFixedParameters(transform->GetFixedParameters());

  auto resample = ResampleFilterType::New();

  resample->SetTransform(finalTransform);
  resample->SetInput(movingImage);

  resample->SetSize(fixedImage->GetLargestPossibleRegion().GetSize());
  resample->SetOutputOrigin(fixedImage->GetOrigin());
  resample->SetOutputSpacing(fixedImage->GetSpacing());
  resample->SetOutputDirection(fixedImage->GetDirection());
  resample->SetDefaultPixelValue(100);

  itk::WriteImage(resample->GetOutput(), argv[3]);

  return EXIT_SUCCESS;
}
