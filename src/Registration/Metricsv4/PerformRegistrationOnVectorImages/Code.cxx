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

#include "itkMeanSquaresImageToImageMetricv4.h"
#include "itkGradientDescentOptimizerv4.h"
#include "itkRegistrationParameterScalesFromPhysicalShift.h"
#include "itkVectorImageToImageMetricTraitsv4.h"

#include "itkGaussianSmoothingOnUpdateDisplacementFieldTransform.h"

#include "itkCastImageFilter.h"

#include "itkCommand.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include <iomanip>

int
main(int argc, char * argv[])
{

  if (argc < 4)
  {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " fixedImageFile movingImageFile ";
    std::cerr << " resampledMovingImageFile ";
    std::cerr << " [numberOfAffineIterations numberOfDisplacementIterations] ";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }
  const char * fixedImageFile = argv[1];
  const char * movingImageFile = argv[2];
  const char * resampledMovingImageFile = argv[3];

  unsigned int numberOfAffineIterations = 2;
  unsigned int numberOfDisplacementIterations = 2;
  if (argc >= 5)
  {
    numberOfAffineIterations = std::stoi(argv[4]);
  }
  if (argc >= 6)
  {
    numberOfDisplacementIterations = std::stoi(argv[5]);
  }

  constexpr unsigned int Dimension = 2;

  // The input images have red, blue, and green pixel components.
  constexpr unsigned int NumberOfPixelComponents = 3;
  using PixelComponentType = float;
  using InputPixelType = itk::Vector<PixelComponentType, NumberOfPixelComponents>;
  using InputImageType = itk::Image<InputPixelType, Dimension>;

  using ParametersValueType = double;

  InputImageType::Pointer fixedImage = itk::ReadImage<InputImageType>(fixedImageFile);
  InputImageType::Pointer movingImage = itk::ReadImage<InputImageType>(movingImageFile);

  using AffineTransformType = itk::AffineTransform<ParametersValueType, Dimension>;
  auto affineTransform = AffineTransformType::New();

  using DisplacementTransformType =
    itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<ParametersValueType, Dimension>;
  auto displacementTransform = DisplacementTransformType::New();

  using DisplacementFieldType = DisplacementTransformType::DisplacementFieldType;
  auto displacementField = DisplacementFieldType::New();

  // Set the displacement field to be the same as the fixed image region, which will
  // act by default as the virtual domain in this example.
  displacementField->SetRegions(fixedImage->GetLargestPossibleRegion());
  // make sure the displacement field has the same spatial information as the image
  displacementField->CopyInformation(fixedImage);
  std::cout << "fixedImage->GetLargestPossibleRegion(): " << fixedImage->GetLargestPossibleRegion() << std::endl;
  displacementField->Allocate();
  // Fill it with 0's
  DisplacementTransformType::OutputVectorType zeroVector{};
  displacementField->FillBuffer(zeroVector);
  // Assign to transform
  displacementTransform->SetDisplacementField(displacementField);
  displacementTransform->SetGaussianSmoothingVarianceForTheUpdateField(5.0);
  displacementTransform->SetGaussianSmoothingVarianceForTheTotalField(6.0);

  // Identity transform for fixed image
  using IdentityTransformType = itk::IdentityTransform<ParametersValueType, Dimension>;
  auto identityTransform = IdentityTransformType::New();

  // The metric
  using VirtualImageType = itk::Image<double, Dimension>;
  using MetricTraitsType =
    itk::VectorImageToImageMetricTraitsv4<InputImageType, InputImageType, VirtualImageType, InputPixelType::Length>;
  using MetricType =
    itk::MeanSquaresImageToImageMetricv4<InputImageType, InputImageType, VirtualImageType, double, MetricTraitsType>;
  using PointSetType = MetricType::FixedSampledPointSetType;
  auto metric = MetricType::New();

  using PointType = PointSetType::PointType;
  auto                                              pointSet = PointSetType::New();
  itk::ImageRegionIteratorWithIndex<InputImageType> fixedImageIt(fixedImage, fixedImage->GetLargestPossibleRegion());
  itk::SizeValueType                                index = 0;
  itk::SizeValueType                                count = 0;
  for (fixedImageIt.GoToBegin(); !fixedImageIt.IsAtEnd(); ++fixedImageIt)
  {
    // take every N^th point
    if (count % 2 == 0)
    {
      PointType point;
      fixedImage->TransformIndexToPhysicalPoint(fixedImageIt.GetIndex(), point);
      pointSet->SetPoint(index, point);
      ++index;
    }
    ++count;
  }
  metric->SetFixedSampledPointSet(pointSet);
  metric->SetUseSampledPointSet(true);


  // Assign images and transforms.
  // By not setting a virtual domain image or virtual domain settings,
  // the metric will use the fixed image for the virtual domain.
  metric->SetFixedImage(fixedImage);
  metric->SetMovingImage(movingImage);
  metric->SetFixedTransform(identityTransform);
  metric->SetMovingTransform(affineTransform);
  const bool gaussian = false;
  metric->SetUseMovingImageGradientFilter(gaussian);
  metric->SetUseFixedImageGradientFilter(gaussian);
  metric->Initialize();

  using RegistrationParameterScalesFromShiftType = itk::RegistrationParameterScalesFromPhysicalShift<MetricType>;
  RegistrationParameterScalesFromShiftType::Pointer shiftScaleEstimator =
    RegistrationParameterScalesFromShiftType::New();
  shiftScaleEstimator->SetMetric(metric);


  //
  // Affine registration
  //
  std::cout << "First do an affine registration..." << std::endl;
  using OptimizerType = itk::GradientDescentOptimizerv4;
  auto optimizer = OptimizerType::New();
  optimizer->SetMetric(metric);
  optimizer->SetNumberOfIterations(numberOfAffineIterations);
  optimizer->SetScalesEstimator(shiftScaleEstimator);
  optimizer->StartOptimization();
  std::cout << "After optimization affine parameters are: " << affineTransform->GetParameters() << std::endl;

  //
  // Deformable registration
  //
  std::cout << "Now, add the displacement field to the composite transform..." << std::endl;
  using CompositeType = itk::CompositeTransform<ParametersValueType, Dimension>;
  auto compositeTransform = CompositeType::New();
  compositeTransform->AddTransform(affineTransform);
  compositeTransform->AddTransform(displacementTransform);
  // Optimize only the displacement field, but still using the
  // previously computed affine transformation.
  compositeTransform->SetOnlyMostRecentTransformToOptimizeOn();
  metric->SetMovingTransform(compositeTransform);
  metric->SetUseSampledPointSet(false);
  metric->Initialize();

  // Optimizer
  optimizer->SetScalesEstimator(shiftScaleEstimator);
  optimizer->SetMetric(metric);
  optimizer->SetNumberOfIterations(numberOfDisplacementIterations);
  try
  {
    if (numberOfDisplacementIterations > 0)
    {
      optimizer->StartOptimization();
    }
    else
    {
      std::cout << "*** Skipping displacement field optimization.\n";
    }
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  // Warp the image with the displacement field
  using ResampleFilterType = itk::ResampleImageFilter<InputImageType, InputImageType>;
  auto resampler = ResampleFilterType::New();
  resampler->SetTransform(compositeTransform);
  resampler->SetInput(movingImage);
  resampler->SetReferenceImage(fixedImage);
  resampler->SetUseReferenceImage(true);

  // Write the warped image into a file
  using OutputPixelType = itk::Vector<unsigned char, NumberOfPixelComponents>;
  using OutputImageType = itk::Image<OutputPixelType, Dimension>;
  using CastFilterType = itk::CastImageFilter<InputImageType, OutputImageType>;
  auto caster = CastFilterType::New();
  caster->SetInput(resampler->GetOutput());

  try
  {
    itk::WriteImage(caster->GetOutput(), resampledMovingImageFile);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
