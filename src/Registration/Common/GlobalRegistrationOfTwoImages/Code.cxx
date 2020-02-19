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
#include "itkCastImageFilter.h"
#include "itkEllipseSpatialObject.h"
#include "itkImage.h"
#include "itkImageRegistrationMethod.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMeanSquaresImageToImageMetric.h"
#include "itkRegularStepGradientDescentOptimizer.h"
#include "itkResampleImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkSpatialObjectToImageFilter.h"
#include "itkTranslationTransform.h"

constexpr unsigned int Dimension = 2;
using PixelType = unsigned char;

using ImageType = itk::Image<PixelType, Dimension>;

static void
CreateEllipseImage(ImageType::Pointer image);
static void
CreateSphereImage(ImageType::Pointer image);

int
main(int, char *[])
{
  //  The transform that will map the fixed image into the moving image.
  using TransformType = itk::TranslationTransform<double, Dimension>;

  //  An optimizer is required to explore the parameter space of the transform
  //  in search of optimal values of the metric.
  using OptimizerType = itk::RegularStepGradientDescentOptimizer;

  //  The metric will compare how well the two images match each other. Metric
  //  types are usually parameterized by the image types as it can be seen in
  //  the following type declaration.
  using MetricType = itk::MeanSquaresImageToImageMetric<ImageType, ImageType>;

  //  Finally, the type of the interpolator is declared. The interpolator will
  //  evaluate the intensities of the moving image at non-grid positions.
  using InterpolatorType = itk::LinearInterpolateImageFunction<ImageType, double>;

  //  The registration method type is instantiated using the types of the
  //  fixed and moving images. This class is responsible for interconnecting
  //  all the components that we have described so far.
  using RegistrationType = itk::ImageRegistrationMethod<ImageType, ImageType>;

  // Create components
  MetricType::Pointer       metric = MetricType::New();
  TransformType::Pointer    transform = TransformType::New();
  OptimizerType::Pointer    optimizer = OptimizerType::New();
  InterpolatorType::Pointer interpolator = InterpolatorType::New();
  RegistrationType::Pointer registration = RegistrationType::New();

  // Each component is now connected to the instance of the registration method.
  registration->SetMetric(metric);
  registration->SetOptimizer(optimizer);
  registration->SetTransform(transform);
  registration->SetInterpolator(interpolator);

  // Get the two images
  ImageType::Pointer fixedImage = ImageType::New();
  ImageType::Pointer movingImage = ImageType::New();

  CreateSphereImage(fixedImage);
  CreateEllipseImage(movingImage);

  // Write the two synthetic inputs
  using WriterType = itk::ImageFileWriter<ImageType>;

  WriterType::Pointer fixedWriter = WriterType::New();
  fixedWriter->SetFileName("fixed.png");
  fixedWriter->SetInput(fixedImage);
  fixedWriter->Update();

  WriterType::Pointer movingWriter = WriterType::New();
  movingWriter->SetFileName("moving.png");
  movingWriter->SetInput(movingImage);
  movingWriter->Update();

  // Set the registration inputs
  registration->SetFixedImage(fixedImage);
  registration->SetMovingImage(movingImage);

  registration->SetFixedImageRegion(fixedImage->GetLargestPossibleRegion());

  //  Initialize the transform
  using ParametersType = RegistrationType::ParametersType;
  ParametersType initialParameters(transform->GetNumberOfParameters());

  initialParameters[0] = 0.0; // Initial offset along X
  initialParameters[1] = 0.0; // Initial offset along Y

  registration->SetInitialTransformParameters(initialParameters);

  optimizer->SetMaximumStepLength(4.00);
  optimizer->SetMinimumStepLength(0.01);

  // Set a stopping criterion
  optimizer->SetNumberOfIterations(200);

  // Connect an observer
  // CommandIterationUpdate::Pointer observer = CommandIterationUpdate::New();
  // optimizer->AddObserver( itk::IterationEvent(), observer );

  try
  {
    registration->Update();
  }
  catch (itk::ExceptionObject & err)
  {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
  }

  //  The result of the registration process is an array of parameters that
  //  defines the spatial transformation in an unique way. This final result is
  //  obtained using the \code{GetLastTransformParameters()} method.

  ParametersType finalParameters = registration->GetLastTransformParameters();

  //  In the case of the \doxygen{TranslationTransform}, there is a
  //  straightforward interpretation of the parameters.  Each element of the
  //  array corresponds to a translation along one spatial dimension.

  const double TranslationAlongX = finalParameters[0];
  const double TranslationAlongY = finalParameters[1];

  //  The optimizer can be queried for the actual number of iterations
  //  performed to reach convergence.  The \code{GetCurrentIteration()}
  //  method returns this value. A large number of iterations may be an
  //  indication that the maximum step length has been set too small, which
  //  is undesirable since it results in long computational times.

  const unsigned int numberOfIterations = optimizer->GetCurrentIteration();

  //  The value of the image metric corresponding to the last set of parameters
  //  can be obtained with the \code{GetValue()} method of the optimizer.

  const double bestValue = optimizer->GetValue();

  // Print out results
  //
  std::cout << "Result = " << std::endl;
  std::cout << " Translation X = " << TranslationAlongX << std::endl;
  std::cout << " Translation Y = " << TranslationAlongY << std::endl;
  std::cout << " Iterations    = " << numberOfIterations << std::endl;
  std::cout << " Metric value  = " << bestValue << std::endl;

  //  It is common, as the last step of a registration task, to use the
  //  resulting transform to map the moving image into the fixed image space.
  //  This is easily done with the \doxygen{ResampleImageFilter}. Please
  //  refer to Section~\ref{sec:ResampleImageFilter} for details on the use
  //  of this filter.  First, a ResampleImageFilter type is instantiated
  //  using the image types. It is convenient to use the fixed image type as
  //  the output type since it is likely that the transformed moving image
  //  will be compared with the fixed image.

  using ResampleFilterType = itk::ResampleImageFilter<ImageType, ImageType>;

  //  A resampling filter is created and the moving image is connected as  its input.

  ResampleFilterType::Pointer resampler = ResampleFilterType::New();
  resampler->SetInput(movingImage);

  //  The Transform that is produced as output of the Registration method is
  //  also passed as input to the resampling filter. Note the use of the
  //  methods \code{GetOutput()} and \code{Get()}. This combination is needed
  //  here because the registration method acts as a filter whose output is a
  //  transform decorated in the form of a \doxygen{DataObject}. For details in
  //  this construction you may want to read the documentation of the
  //  \doxygen{DataObjectDecorator}.

  resampler->SetTransform(registration->GetOutput()->Get());

  //  As described in Section \ref{sec:ResampleImageFilter}, the
  //  ResampleImageFilter requires additional parameters to be specified, in
  //  particular, the spacing, origin and size of the output image. The default
  //  pixel value is also set to a distinct gray level in order to highlight
  //  the regions that are mapped outside of the moving image.

  resampler->SetSize(fixedImage->GetLargestPossibleRegion().GetSize());
  resampler->SetOutputOrigin(fixedImage->GetOrigin());
  resampler->SetOutputSpacing(fixedImage->GetSpacing());
  resampler->SetOutputDirection(fixedImage->GetDirection());
  resampler->SetDefaultPixelValue(100);

  //  The output of the filter is passed to a writer that will store the
  //  image in a file. An \doxygen{CastImageFilter} is used to convert the
  //  pixel type of the resampled image to the final type used by the
  //  writer. The cast and writer filters are instantiated below.

  using CastFilterType = itk::CastImageFilter<ImageType, ImageType>;

  WriterType::Pointer     writer = WriterType::New();
  CastFilterType::Pointer caster = CastFilterType::New();
  writer->SetFileName("output.png");

  caster->SetInput(resampler->GetOutput());
  writer->SetInput(caster->GetOutput());
  writer->Update();

  /*
  //  The fixed image and the transformed moving image can easily be compared
  //  using the \doxygen{SubtractImageFilter}. This pixel-wise filter computes
  //  the difference between homologous pixels of its two input images.


  using DifferenceFilterType = itk::SubtractImageFilter<
      FixedImageType,
      FixedImageType,
      FixedImageType >;

  DifferenceFilterType::Pointer difference = DifferenceFilterType::New();

  difference->SetInput1( fixedImageReader->GetOutput() );
  difference->SetInput2( resampler->GetOutput() );
  */


  return EXIT_SUCCESS;
}

void
CreateEllipseImage(ImageType::Pointer image)
{
  using EllipseType = itk::EllipseSpatialObject<Dimension>;

  using SpatialObjectToImageFilterType = itk::SpatialObjectToImageFilter<EllipseType, ImageType>;

  SpatialObjectToImageFilterType::Pointer imageFilter = SpatialObjectToImageFilterType::New();

  ImageType::SizeType size;
  size[0] = 100;
  size[1] = 100;

  imageFilter->SetSize(size);

  ImageType::SpacingType spacing;
  spacing.Fill(1);
  imageFilter->SetSpacing(spacing);

  EllipseType::Pointer   ellipse = EllipseType::New();
  EllipseType::ArrayType radiusArray;
  radiusArray[0] = 10;
  radiusArray[1] = 20;
  ellipse->SetRadiusInObjectSpace(radiusArray);

  using TransformType = EllipseType::TransformType;
  TransformType::Pointer transform = TransformType::New();
  transform->SetIdentity();

  TransformType::OutputVectorType translation;
  translation[0] = 65;
  translation[1] = 45;
  transform->Translate(translation, false);

  ellipse->SetObjectToParentTransform(transform);

  imageFilter->SetInput(ellipse);

  ellipse->SetDefaultInsideValue(255);
  ellipse->SetDefaultOutsideValue(0);
  imageFilter->SetUseObjectValue(true);
  imageFilter->SetOutsideValue(0);

  imageFilter->Update();

  image->Graft(imageFilter->GetOutput());
}

void
CreateSphereImage(ImageType::Pointer image)
{
  using EllipseType = itk::EllipseSpatialObject<Dimension>;

  using SpatialObjectToImageFilterType = itk::SpatialObjectToImageFilter<EllipseType, ImageType>;

  SpatialObjectToImageFilterType::Pointer imageFilter = SpatialObjectToImageFilterType::New();

  ImageType::SizeType size;
  size[0] = 100;
  size[1] = 100;

  imageFilter->SetSize(size);

  ImageType::SpacingType spacing;
  spacing.Fill(1);
  imageFilter->SetSpacing(spacing);

  EllipseType::Pointer   ellipse = EllipseType::New();
  EllipseType::ArrayType radiusArray;
  radiusArray[0] = 10;
  radiusArray[1] = 10;
  ellipse->SetRadiusInObjectSpace(radiusArray);

  using TransformType = EllipseType::TransformType;
  TransformType::Pointer transform = TransformType::New();
  transform->SetIdentity();

  TransformType::OutputVectorType translation;
  translation[0] = 50;
  translation[1] = 50;
  transform->Translate(translation, false);

  ellipse->SetObjectToParentTransform(transform);

  imageFilter->SetInput(ellipse);

  ellipse->SetDefaultInsideValue(255);
  ellipse->SetDefaultOutsideValue(0);
  imageFilter->SetUseObjectValue(true);
  imageFilter->SetOutsideValue(0);

  imageFilter->Update();

  image->Graft(imageFilter->GetOutput());
}
