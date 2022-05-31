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
#include "itkScalarChanAndVeseSparseLevelSetImageFilter.h"
#include "itkScalarChanAndVeseLevelSetFunction.h"
#include "itkScalarChanAndVeseLevelSetFunctionData.h"
#include "itkConstrainedRegionBasedLevelSetFunctionSharedData.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImage.h"
#include "itkAtanRegularizedHeavisideStepFunction.h"

int
main(int argc, char ** argv)
{
  if (argc < 10)
  {
    std::cerr << "Missing arguments" << std::endl;
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " inputLevelSetImage1 inputLevelSetImage2 inputLevelSetImage3";
    std::cerr << " inputFeatureImage outputLevelSetImage";
    std::cerr << " CurvatureWeight AreaWeight LaplacianWeight";
    std::cerr << " VolumeWeight Volume OverlapWeight" << std::endl;
    return EXIT_FAILURE;
  }

  unsigned int nb_iteration = 50;
  double       rms = 0.;
  double       epsilon = 1.5;
  double       curvature_weight = std::stod(argv[6]);
  double       area_weight = std::stod(argv[7]);
  double       volume_weight = std::stod(argv[8]);
  double       volume = std::stod(argv[9]);
  double       overlap_weight = std::stod(argv[10]);
  double       l1 = 1.;
  double       l2 = 1.;

  constexpr unsigned int Dimension = 2;
  using ScalarPixelType = float;

  using LevelSetImageType = itk::Image<ScalarPixelType, Dimension>;
  using FeatureImageType = itk::Image<unsigned char, Dimension>;
  using OutputImageType = itk::Image<unsigned char, Dimension>;

  using DataHelperType = itk::ScalarChanAndVeseLevelSetFunctionData<LevelSetImageType, FeatureImageType>;

  using SharedDataHelperType =
    itk::ConstrainedRegionBasedLevelSetFunctionSharedData<LevelSetImageType, FeatureImageType, DataHelperType>;

  using LevelSetFunctionType =
    itk::ScalarChanAndVeseLevelSetFunction<LevelSetImageType, FeatureImageType, SharedDataHelperType>;

  using MultiLevelSetType = itk::ScalarChanAndVeseSparseLevelSetImageFilter<LevelSetImageType,
                                                                            FeatureImageType,
                                                                            OutputImageType,
                                                                            LevelSetFunctionType,
                                                                            SharedDataHelperType>;

  using DomainFunctionType = itk::AtanRegularizedHeavisideStepFunction<ScalarPixelType, ScalarPixelType>;

  auto domainFunction = DomainFunctionType::New();
  domainFunction->SetEpsilon(epsilon);

  LevelSetImageType::Pointer contourImage1 = itk::ReadImage<LevelSetImageType>(argv[1]);
  LevelSetImageType::Pointer contourImage2 = itk::ReadImage<LevelSetImageType>(argv[2]);
  LevelSetImageType::Pointer contourImage3 = itk::ReadImage<LevelSetImageType>(argv[3]);
  FeatureImageType::Pointer  featureImage = itk::ReadImage<FeatureImageType>(argv[4]);

  auto levelSetFilter = MultiLevelSetType::New();
  levelSetFilter->SetFunctionCount(3);
  levelSetFilter->SetFeatureImage(featureImage);
  levelSetFilter->SetLevelSet(0, contourImage1);
  levelSetFilter->SetLevelSet(1, contourImage2);
  levelSetFilter->SetLevelSet(2, contourImage3);
  levelSetFilter->SetNumberOfIterations(nb_iteration);
  levelSetFilter->SetMaximumRMSError(rms);
  levelSetFilter->SetUseImageSpacing(1);
  levelSetFilter->SetInPlace(false);

  for (unsigned int i = 0; i < 3; ++i)
  {
    levelSetFilter->GetDifferenceFunction(i)->SetDomainFunction(domainFunction);
    levelSetFilter->GetDifferenceFunction(i)->SetCurvatureWeight(curvature_weight);
    levelSetFilter->GetDifferenceFunction(i)->SetAreaWeight(area_weight);
    levelSetFilter->GetDifferenceFunction(i)->SetOverlapPenaltyWeight(overlap_weight);
    levelSetFilter->GetDifferenceFunction(i)->SetVolumeMatchingWeight(volume_weight);
    levelSetFilter->GetDifferenceFunction(i)->SetVolume(volume);
    levelSetFilter->GetDifferenceFunction(i)->SetLambda1(l1);
    levelSetFilter->GetDifferenceFunction(i)->SetLambda2(l2);
  }

  levelSetFilter->Update();

  try
  {
    itk::WriteImage(levelSetFilter->GetOutput(), argv[5]);
  }
  catch (const itk::ExceptionObject & excep)
  {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << excep << std::endl;
    return -1;
  }

  return EXIT_SUCCESS;
}
