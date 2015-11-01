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


int main( int argc, char *argv[] )
{
  if( argc != 6 )
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

  const    unsigned int    Dimension = 2;
  typedef  float           PixelType;

  typedef itk::Image< PixelType, Dimension >  FixedImageType;
  typedef itk::Image< PixelType, Dimension >  MovingImageType;

  typedef itk::TranslationTransform< double, Dimension > TransformType;
  typedef itk::RegularStepGradientDescentOptimizerv4<double> OptimizerType;

  typedef itk::MeanSquaresImageToImageMetricv4<
                                          FixedImageType,
                                          MovingImageType >    MetricType;

  typedef itk::ImageRegistrationMethodv4<
                                    FixedImageType,
                                    MovingImageType   >    RegistrationType;

  MetricType::Pointer         metric        = MetricType::New();
  OptimizerType::Pointer      optimizer     = OptimizerType::New();
  RegistrationType::Pointer   registration  = RegistrationType::New();
  TransformType::Pointer initialTransform   = TransformType::New();

  registration->SetInitialTransform(     initialTransform     );
  registration->SetMetric(        metric        );
  registration->SetOptimizer(     optimizer     );

  typedef itk::LinearInterpolateImageFunction<
                                        FixedImageType,
                                        double > FixedLinearInterpolatorType;

  typedef itk::LinearInterpolateImageFunction<
                                        MovingImageType,
                                        double > MovingLinearInterpolatorType;

  FixedLinearInterpolatorType::Pointer fixedInterpolator =
    FixedLinearInterpolatorType::New();
  MovingLinearInterpolatorType::Pointer movingInterpolator =
    MovingLinearInterpolatorType::New();

  metric->SetFixedInterpolator(  fixedInterpolator  );
  metric->SetMovingInterpolator(  movingInterpolator  );

  typedef itk::ImageFileReader< FixedImageType  >   FixedImageReaderType;
  typedef itk::ImageFileReader< MovingImageType >   MovingImageReaderType;
  FixedImageReaderType::Pointer   fixedImageReader     = FixedImageReaderType::New();
  MovingImageReaderType::Pointer  movingImageReader    = MovingImageReaderType::New();

  fixedImageReader->SetFileName( fixedImageFile );
  movingImageReader->SetFileName( movingImageFile );

  registration->SetFixedImage(    fixedImageReader->GetOutput()    );
  registration->SetMovingImage(   movingImageReader->GetOutput()   );

  TransformType::Pointer movingInitialTransform = TransformType::New();

  TransformType::ParametersType initialParameters(
    movingInitialTransform->GetNumberOfParameters() );
  initialParameters[0] = 0.0;
  initialParameters[1] = 0.0;

  movingInitialTransform->SetParameters( initialParameters );

  registration->SetMovingInitialTransform( movingInitialTransform );

  TransformType::Pointer   identityTransform = TransformType::New();
  identityTransform->SetIdentity();

  registration->SetFixedInitialTransform( identityTransform );

  optimizer->SetLearningRate( 4 );
  optimizer->SetMinimumStepLength( 0.001 );
  optimizer->SetRelaxationFactor( 0.5 );
  optimizer->SetNumberOfIterations( 200 );

  const unsigned int numberOfLevels = 1;

  RegistrationType::ShrinkFactorsArrayType shrinkFactorsPerLevel;
  shrinkFactorsPerLevel.SetSize( 1 );
  shrinkFactorsPerLevel[0] = 1;

  RegistrationType::SmoothingSigmasArrayType smoothingSigmasPerLevel;
  smoothingSigmasPerLevel.SetSize( 1 );
  smoothingSigmasPerLevel[0] = 0;

  registration->SetNumberOfLevels ( numberOfLevels );
  registration->SetSmoothingSigmasPerLevel( smoothingSigmasPerLevel );
  registration->SetShrinkFactorsPerLevel( shrinkFactorsPerLevel );

  try
    {
    registration->Update();
    std::cout << "Optimizer stop condition: "
    << registration->GetOptimizer()->GetStopConditionDescription()
    << std::endl;
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
    }

  TransformType::ConstPointer transform =
        dynamic_cast< const TransformType *> ( registration->GetTransform() );

  TransformType::ParametersType finalParameters = transform->GetParameters();
  const double TranslationAlongX = finalParameters[0];
  const double TranslationAlongY = finalParameters[1];

  const unsigned int numberOfIterations = optimizer->GetCurrentIteration();

  const double bestValue = optimizer->GetValue();

  std::cout << "Result = " << std::endl;
  std::cout << " Translation X = " << TranslationAlongX  << std::endl;
  std::cout << " Translation Y = " << TranslationAlongY  << std::endl;
  std::cout << " Iterations    = " << numberOfIterations << std::endl;
  std::cout << " Metric value  = " << bestValue          << std::endl;

  typedef itk::CompositeTransform<
                                 double,
                                 Dimension > CompositeTransformType;
  CompositeTransformType::Pointer outputCompositeTransform =
    CompositeTransformType::New();
  outputCompositeTransform->AddTransform( movingInitialTransform );
  outputCompositeTransform->AddTransform(
    registration->GetModifiableTransform() );

  typedef itk::ResampleImageFilter<
                            MovingImageType,
                            FixedImageType >    ResampleFilterType;

  ResampleFilterType::Pointer resampler = ResampleFilterType::New();
  resampler->SetInput( movingImageReader->GetOutput() );

  resampler->SetTransform( outputCompositeTransform );

  FixedImageType::Pointer fixedImage = fixedImageReader->GetOutput();
  resampler->SetSize( fixedImage->GetLargestPossibleRegion().GetSize() );
  resampler->SetOutputOrigin(  fixedImage->GetOrigin() );
  resampler->SetOutputSpacing( fixedImage->GetSpacing() );
  resampler->SetOutputDirection( fixedImage->GetDirection() );
  resampler->SetDefaultPixelValue( 100 );

  typedef unsigned char                            OutputPixelType;

  typedef itk::Image< OutputPixelType, Dimension > OutputImageType;

  typedef itk::CastImageFilter<
                        FixedImageType,
                        OutputImageType >          CastFilterType;

  typedef itk::ImageFileWriter< OutputImageType >  WriterType;

  WriterType::Pointer      writer =  WriterType::New();
  CastFilterType::Pointer  caster =  CastFilterType::New();

  writer->SetFileName( outputImageFile );

  caster->SetInput( resampler->GetOutput() );
  writer->SetInput( caster->GetOutput()   );
  writer->Update();

  typedef itk::SubtractImageFilter<
                                  FixedImageType,
                                  FixedImageType,
                                  FixedImageType > DifferenceFilterType;

  DifferenceFilterType::Pointer difference = DifferenceFilterType::New();

  difference->SetInput1( fixedImageReader->GetOutput() );
  difference->SetInput2( resampler->GetOutput() );

  typedef itk::RescaleIntensityImageFilter<
                                  FixedImageType,
                                  OutputImageType >   RescalerType;

  RescalerType::Pointer intensityRescaler = RescalerType::New();

  intensityRescaler->SetInput( difference->GetOutput() );
  intensityRescaler->SetOutputMinimum( itk::NumericTraits< OutputPixelType >::min() );
  intensityRescaler->SetOutputMaximum( itk::NumericTraits< OutputPixelType >::max() );

  resampler->SetDefaultPixelValue( 1 );

  WriterType::Pointer writer2 = WriterType::New();
  writer2->SetInput( intensityRescaler->GetOutput() );

  writer2->SetFileName( differenceImageAfterFile );
  writer2->Update();

  resampler->SetTransform( identityTransform );

  writer2->SetFileName( differenceImageBeforeFile );
  writer2->Update();

  return EXIT_SUCCESS;
}
