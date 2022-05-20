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
#include "itkVector.h"
#include "itkListSample.h"
#include "itkGaussianMixtureModelComponent.h"
#include "itkExpectationMaximizationMixtureModelEstimator.h"
#include "itkSampleClassifierFilter.h"
#include "itkMaximumDecisionRule.h"
#include "itkImageToListSampleFilter.h"
#include "itkCovariantVector.h"
#include "itkImageRegionIterator.h"
#include "itkSimpleFilterWatcher.h"

using PixelType = itk::CovariantVector<unsigned char, 3>;
using ImageType = itk::Image<PixelType, 2>;

#undef USE_CONTROLLED_IMAGE
#ifdef USE_CONTROLLED_IMAGE
static void
ControlledImage(ImageType::Pointer image);
#else
static void
RandomImage(ImageType::Pointer image);
#endif

int
main(int /*argc*/, char * /*argv*/[])
{

  auto image = ImageType::New();

#ifdef USE_CONTROLLED_IMAGE
  ControlledImage(image);
#else
  RandomImage(image);
#endif

  using ImageToListSampleFilterType = itk::Statistics::ImageToListSampleFilter<ImageType>;
  auto imageToListSampleFilter = ImageToListSampleFilterType::New();
  imageToListSampleFilter->SetInput(image);
  imageToListSampleFilter->Update();

  unsigned int numberOfClasses = 3;

  using ParametersType = itk::Array<double>;
  ParametersType params(numberOfClasses + numberOfClasses * numberOfClasses); // 3 for means and 9 for 3x3 covariance

  // Create the first set (for the first cluster/model) of initial parameters
  std::vector<ParametersType> initialParameters(numberOfClasses);
  for (unsigned int i = 0; i < 3; ++i)
  {
    params[i] = 5.0; // mean of dimension i
  }
  unsigned int counter = 0;
  for (unsigned int i = 0; i < 3; ++i)
  {
    for (unsigned int j = 0; j < 3; ++j)
    {
      if (i == j)
      {
        params[3 + counter] = 5; // diagonal
      }
      else
      {
        params[3 + counter] = 0; // off-diagonal
      }
      counter++;
    }
  }


  initialParameters[0] = params;

  // Create the second set (for the second cluster/model) of initial parameters
  params[0] = 210.0;
  params[1] = 5.0;
  params[2] = 5.0;
  counter = 0;
  for (unsigned int i = 0; i < 3; ++i)
  {
    for (unsigned int j = 0; j < 3; ++j)
    {
      if (i == j)
      {
        params[3 + counter] = 5; // diagonal
      }
      else
      {
        params[3 + counter] = 0; // off-diagonal
      }
      counter++;
    }
  }
  initialParameters[1] = params;

  // Create the third set (for the third cluster/model) of initial parameters
  params[0] = 5.0;
  params[1] = 210.0;
  params[2] = 5.0;
  counter = 0;
  for (unsigned int i = 0; i < 3; ++i)
  {
    for (unsigned int j = 0; j < 3; ++j)
    {
      if (i == j)
      {
        params[3 + counter] = 5; // diagonal
      }
      else
      {
        params[3 + counter] = 0; // off-diagonal
      }
      counter++;
    }
  }
  initialParameters[2] = params;

  std::cout << "Initial parameters: " << std::endl;
  for (unsigned int i = 0; i < numberOfClasses; ++i)
  {
    std::cout << initialParameters[i] << std::endl;
  }

  using ComponentType = itk::Statistics::GaussianMixtureModelComponent<ImageToListSampleFilterType::ListSampleType>;

  std::cout << "Number of samples: " << imageToListSampleFilter->GetOutput()->GetTotalFrequency() << std::endl;

  // Create the components
  std::vector<ComponentType::Pointer> components;
  for (unsigned int i = 0; i < numberOfClasses; ++i)
  {
    components.push_back(ComponentType::New());
    (components[i])->SetSample(imageToListSampleFilter->GetOutput());
    (components[i])->SetParameters(initialParameters[i]);
  }


  using EstimatorType =
    itk::Statistics::ExpectationMaximizationMixtureModelEstimator<ImageToListSampleFilterType::ListSampleType>;
  auto estimator = EstimatorType::New();

  estimator->SetSample(imageToListSampleFilter->GetOutput());
  estimator->SetMaximumIteration(200);

  itk::Array<double> initialProportions(numberOfClasses);
  initialProportions[0] = 0.33;
  initialProportions[1] = 0.33;
  initialProportions[2] = 0.33;

  std::cout << "Initial proportions: " << initialProportions << std::endl;

  estimator->SetInitialProportions(initialProportions);

  for (unsigned int i = 0; i < numberOfClasses; ++i)
  {
    estimator->AddComponent(components[i]);
  }
  // itk::SimpleFilterWatcher watcher(estimator);
  estimator->Update();

  // Output the results
  for (unsigned int i = 0; i < numberOfClasses; ++i)
  {
    std::cout << "Cluster[" << i << "]" << std::endl;
    std::cout << "    Parameters:" << std::endl;
    std::cout << "         " << (components[i])->GetFullParameters() << std::endl;
    std::cout << "    Proportion: ";
    // Outputs: // mean of dimension 1, mean of dimension 2, covariance(0,0), covariance(0,1), covariance(1,0),
    // covariance(1,1)
    std::cout << "         " << estimator->GetProportions()[i] << std::endl;
  }

  // Display the membership of each sample
  using FilterType = itk::Statistics::SampleClassifierFilter<ImageToListSampleFilterType::ListSampleType>;

  using DecisionRuleType = itk::Statistics::MaximumDecisionRule;
  auto decisionRule = DecisionRuleType::New();

  using ClassLabelVectorObjectType = FilterType::ClassLabelVectorObjectType;
  using ClassLabelVectorType = FilterType::ClassLabelVectorType;

  auto                   classLabelsObject = ClassLabelVectorObjectType::New();
  ClassLabelVectorType & classLabelVector = classLabelsObject->Get();

  using ClassLabelType = FilterType::ClassLabelType;

  ClassLabelType class0 = 0;
  classLabelVector.push_back(class0);

  ClassLabelType class1 = 1;
  classLabelVector.push_back(class1);

  ClassLabelType class2 = 2;
  classLabelVector.push_back(class2);

  auto sampleClassifierFilter = FilterType::New();
  sampleClassifierFilter->SetInput(imageToListSampleFilter->GetOutput());
  sampleClassifierFilter->SetNumberOfClasses(numberOfClasses);
  sampleClassifierFilter->SetClassLabels(classLabelsObject);
  sampleClassifierFilter->SetDecisionRule(decisionRule);
  sampleClassifierFilter->SetMembershipFunctions(estimator->GetOutput());
  sampleClassifierFilter->Update();

  const FilterType::MembershipSampleType *        membershipSample = sampleClassifierFilter->GetOutput();
  FilterType::MembershipSampleType::ConstIterator iter = membershipSample->Begin();

  while (iter != membershipSample->End())
  {
    std::cout << (int)iter.GetMeasurementVector()[0] << " " << (int)iter.GetMeasurementVector()[1] << " "
              << (int)iter.GetMeasurementVector()[2] << " : " << iter.GetClassLabel() << std::endl;
    ++iter;
  }

  return EXIT_SUCCESS;
}

#ifdef USE_CONTROLLED_IMAGE
void
ControlledImage(ImageType::Pointer image)
{
  // Create an image
  ImageType::RegionType region;
  ImageType::IndexType  start;
  start[0] = 0;
  start[1] = 0;

  ImageType::SizeType size;
  size[0] = 10;
  size[1] = 10;

  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  // Make a red and a green square
  itk::CovariantVector<unsigned char, 3> green;
  green[0] = 0;
  green[1] = 255;
  green[2] = 0;

  itk::CovariantVector<unsigned char, 3> red;
  red[0] = 255;
  red[1] = 0;
  red[2] = 0;

  itk::CovariantVector<unsigned char, 3> black;
  black[0] = 0;
  black[1] = 0;
  black[2] = 0;

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);
  imageIterator.GoToBegin();

  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] > 2 && imageIterator.GetIndex()[0] < 5 && imageIterator.GetIndex()[1] > 2 &&
        imageIterator.GetIndex()[1] < 5)
    {
      imageIterator.Set(green);
    }
    else if (imageIterator.GetIndex()[0] > 6 && imageIterator.GetIndex()[0] < 9 && imageIterator.GetIndex()[1] > 6 &&
             imageIterator.GetIndex()[1] < 9)
    {
      imageIterator.Set(red);
    }
    else
    {
      imageIterator.Set(black);
    }
    ++imageIterator;
  }
}
#else

void
RandomImage(ImageType::Pointer image)
{
  // Create an image
  ImageType::RegionType region;
  ImageType::IndexType  start;
  start[0] = 0;
  start[1] = 0;

  ImageType::SizeType size;
  size[0] = 10;
  size[1] = 10;

  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);
  imageIterator.GoToBegin();

  while (!imageIterator.IsAtEnd())
  {
    // Get a random color
    itk::CovariantVector<unsigned char, 3> pixel;
    pixel[0] = rand() * 255;
    pixel[1] = rand() * 255;
    pixel[2] = rand() * 255;
    imageIterator.Set(pixel);
    ++imageIterator;
  }
}
#endif
