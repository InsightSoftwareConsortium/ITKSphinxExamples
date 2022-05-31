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
#include "itkImageFileReader.h"
#include "itkEuler2DTransform.h"
#include "itkExhaustiveOptimizerv4.h"
#include "itkMeanSquaresImageToImageMetricv4.h"
#include "itkCenteredTransformInitializer.h"
#include "itkImageRegistrationMethodv4.h"
#include "itkImage.h"

//  Command observer to monitor the evolution of the registration process.
//
#include "itkCommand.h"
class CommandIterationUpdate : public itk::Command
{
public:
  using Self = CommandIterationUpdate;
  using Superclass = itk::Command;
  using Pointer = itk::SmartPointer<Self>;
  itkNewMacro(Self);

protected:
  CommandIterationUpdate() = default;

public:
  using OptimizerType = itk::ExhaustiveOptimizerv4<double>;
  using OptimizerPointer = const OptimizerType *;

  void
  Execute(itk::Object * caller, const itk::EventObject & event) override
  {
    Execute((const itk::Object *)caller, event);
  }

  void
  Execute(const itk::Object * object, const itk::EventObject & event) override
  {
    auto optimizer = static_cast<OptimizerPointer>(object);
    if (!(itk::IterationEvent().CheckEvent(&event)))
    {
      return;
    }
    std::cout << "Iteration: ";
    std::cout << optimizer->GetCurrentIteration() << "   ";
    std::cout << optimizer->GetCurrentIndex() << "   ";
    std::cout << optimizer->GetCurrentValue() << "   ";
    std::cout << optimizer->GetCurrentPosition() << "   ";
    std::cout << std::endl;
  }
};

int
main(int argc, char * argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " fixedImage movingImage" << std::endl;
    return EXIT_FAILURE;
  }
  using FixedImageType = itk::Image<double, 2>;
  using MovingImageType = itk::Image<double, 2>;
  using TransformType = itk::Euler2DTransform<double>;
  using OptimizerType = itk::ExhaustiveOptimizerv4<double>;
  using MetricType = itk::MeanSquaresImageToImageMetricv4<FixedImageType, MovingImageType>;
  using TransformInitializerType = itk::CenteredTransformInitializer<TransformType, FixedImageType, MovingImageType>;
  using RegistrationType = itk::ImageRegistrationMethodv4<FixedImageType, MovingImageType, TransformType>;

  auto fixedImage = FixedImageType::New();
  auto movingImage = MovingImageType::New();
  auto transform = TransformType::New();
  auto metric = MetricType::New();
  auto optimizer = OptimizerType::New();
  auto registration = RegistrationType::New();
  auto initializer = TransformInitializerType::New();

  fixedImage = itk::ReadImage<FixedImageType>(argv[1]);
  movingImage = itk::ReadImage<MovingImageType>(argv[2]);

  // Create the Command observer and register it with the optimizer.
  //
  auto observer = CommandIterationUpdate::New();
  optimizer->AddObserver(itk::IterationEvent(), observer);

  unsigned int             angles = 12;
  OptimizerType::StepsType steps(transform->GetNumberOfParameters());
  steps[0] = int(angles / 2);
  steps[1] = 0;
  steps[2] = 0;
  optimizer->SetNumberOfSteps(steps);

  OptimizerType::ScalesType scales(transform->GetNumberOfParameters());
  scales[0] = 2.0 * itk::Math::pi / angles;
  scales[1] = 1.0;
  scales[2] = 1.0;

  optimizer->SetScales(scales);

  initializer->SetTransform(transform);
  initializer->SetFixedImage(fixedImage);
  initializer->SetMovingImage(movingImage);
  initializer->InitializeTransform();

  // Initialize registration
  registration->SetMetric(metric);
  registration->SetOptimizer(optimizer);
  registration->SetFixedImage(fixedImage);
  registration->SetMovingImage(movingImage);
  registration->SetInitialTransform(transform);
  registration->SetNumberOfLevels(1);
  try
  {
    registration->Update();
    std::cout << "  MinimumMetricValue: " << optimizer->GetMinimumMetricValue() << std::endl;
    std::cout << "  MaximumMetricValue: " << optimizer->GetMaximumMetricValue() << std::endl;
    std::cout << "  MinimumMetricValuePosition: " << optimizer->GetMinimumMetricValuePosition() << std::endl;
    std::cout << "  MaximumMetricValuePosition: " << optimizer->GetMaximumMetricValuePosition() << std::endl;
    std::cout << "  StopConditionDescription: " << optimizer->GetStopConditionDescription() << std::endl;
  }
  catch (const itk::ExceptionObject & err)
  {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
