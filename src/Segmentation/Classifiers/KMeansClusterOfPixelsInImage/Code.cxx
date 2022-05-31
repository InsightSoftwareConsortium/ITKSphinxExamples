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
#include "itkListSample.h"
#include "itkVector.h"
#include "itkImageKmeansModelEstimator.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkImageToListSampleAdaptor.h"
#include "itkDistanceToCentroidMembershipFunction.h"
#include "itkSampleClassifierFilter.h"
#include "itkMinimumDecisionRule.h"
#include "itkImageFileWriter.h"

using MeasurementVectorType = itk::Vector<unsigned char, 3>;
using ColorImageType = itk::Image<MeasurementVectorType, 2>;
using ScalarImageType = itk::Image<unsigned char, 2>;

static void
CreateImage(ColorImageType::Pointer image);

int
main()
{
  // Create a demo image
  auto image = ColorImageType::New();
  CreateImage(image);

  // Compute pixel clusters using KMeans
  using MembershipFunctionType = itk::Statistics::DistanceToCentroidMembershipFunction<MeasurementVectorType>;
  using MembershipFunctionPointer = MembershipFunctionType::Pointer;
  using MembershipFunctionPointerVector = std::vector<MembershipFunctionPointer>;

  using ImageKmeansModelEstimatorType = itk::ImageKmeansModelEstimator<ColorImageType, MembershipFunctionType>;

  auto kmeansEstimator = ImageKmeansModelEstimatorType::New();
  kmeansEstimator->SetInputImage(image);
  kmeansEstimator->SetNumberOfModels(3);
  kmeansEstimator->SetThreshold(0.01);
  kmeansEstimator->SetOffsetAdd(0.01);
  kmeansEstimator->SetOffsetMultiply(0.01);
  kmeansEstimator->SetMaxSplitAttempts(10);
  kmeansEstimator->Update();

  // Classify each pixel
  using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;
  using ClassifierType = itk::Statistics::SampleClassifierFilter<SampleType>;
  auto classifier = ClassifierType::New();

  using DecisionRuleType = itk::Statistics::MinimumDecisionRule;
  auto decisionRule = DecisionRuleType::New();

  classifier->SetDecisionRule(decisionRule);
  classifier->SetNumberOfClasses(3);

  using ClassLabelVectorObjectType = ClassifierType::ClassLabelVectorObjectType;
  using ClassLabelVectorType = ClassifierType::ClassLabelVectorType;
  using MembershipFunctionVectorObjectType = ClassifierType::MembershipFunctionVectorObjectType;
  using MembershipFunctionVectorType = ClassifierType::MembershipFunctionVectorType;

  // Setup membership functions
  MembershipFunctionPointerVector kmeansMembershipFunctions = kmeansEstimator->GetMembershipFunctions();

  MembershipFunctionVectorObjectType::Pointer membershipFunctionsVectorObject =
    MembershipFunctionVectorObjectType::New();
  classifier->SetMembershipFunctions(membershipFunctionsVectorObject);

  MembershipFunctionVectorType & membershipFunctionsVector = membershipFunctionsVectorObject->Get();

  for (auto & kmeansMembershipFunction : kmeansMembershipFunctions)
  {
    membershipFunctionsVector.push_back(kmeansMembershipFunction.GetPointer());
  }

  // Setup class labels
  auto classLabelsObject = ClassLabelVectorObjectType::New();
  classifier->SetClassLabels(classLabelsObject);

  ClassLabelVectorType & classLabelsVector = classLabelsObject->Get();
  classLabelsVector.push_back(50);
  classLabelsVector.push_back(150);
  classLabelsVector.push_back(250);

  // Perform the classification
  using SampleAdaptorType = itk::Statistics::ImageToListSampleAdaptor<ColorImageType>;
  auto sample = SampleAdaptorType::New();
  sample->SetImage(image);

  classifier->SetInput(sample);
  classifier->Update();

  // Prepare the output image
  auto outputImage = ScalarImageType::New();
  outputImage->SetRegions(image->GetLargestPossibleRegion());
  outputImage->Allocate();
  outputImage->FillBuffer(0);

  // Setup the membership iterator
  const ClassifierType::MembershipSampleType *        membershipSample = classifier->GetOutput();
  ClassifierType::MembershipSampleType::ConstIterator membershipIterator = membershipSample->Begin();

  // Setup the output image iterator - this is automatically synchronized with the membership iterator since the sample
  // is an adaptor
  itk::ImageRegionIteratorWithIndex<ScalarImageType> outputIterator(outputImage,
                                                                    outputImage->GetLargestPossibleRegion());
  outputIterator.GoToBegin();

  while (membershipIterator != membershipSample->End())
  {
    int classLabel = membershipIterator.GetClassLabel();
    // std::cout << "Class label: " << classLabel << std::endl;
    outputIterator.Set(classLabel);
    ++membershipIterator;
    ++outputIterator;
  }

  itk::WriteImage(image, "input.mha");
  itk::WriteImage(outputImage, "output.mha");


  return EXIT_SUCCESS;
}

void
CreateImage(ColorImageType::Pointer image)
{
  // Create a black image with a red square and a green square
  ColorImageType::RegionType region;
  ColorImageType::IndexType  start;
  start[0] = 0;
  start[1] = 0;

  ColorImageType::SizeType size;
  size[0] = 200;
  size[1] = 300;

  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ColorImageType> imageIterator(image, region);

  itk::Vector<unsigned char, 3> redPixel;
  redPixel[0] = 255;
  redPixel[1] = 0;
  redPixel[2] = 0;

  itk::Vector<unsigned char, 3> greenPixel;
  greenPixel[0] = 0;
  greenPixel[1] = 255;
  greenPixel[2] = 0;

  itk::Vector<unsigned char, 3> blackPixel;
  blackPixel[0] = 0;
  blackPixel[1] = 0;
  blackPixel[2] = 0;

  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] > 100 && imageIterator.GetIndex()[0] < 150 && imageIterator.GetIndex()[1] > 100 &&
        imageIterator.GetIndex()[1] < 150)
    {
      imageIterator.Set(redPixel);
    }
    else if (imageIterator.GetIndex()[0] > 50 && imageIterator.GetIndex()[0] < 70 && imageIterator.GetIndex()[1] > 50 &&
             imageIterator.GetIndex()[1] < 70)
    {
      imageIterator.Set(greenPixel);
    }
    else
    {
      imageIterator.Set(blackPixel);
    }

    ++imageIterator;
  }
}
