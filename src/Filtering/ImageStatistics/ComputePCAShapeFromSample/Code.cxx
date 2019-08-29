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
/*
Author: Juan Cardelino <juan dot cardelino at gmail dot com>
*/

// ITK
#include "itkBinaryThresholdImageFilter.h"
#include "itkBoundedReciprocalImageFilter.h"
#include "itkChangeInformationImageFilter.h"
#include "itkCommand.h"
#include "itkCurvatureAnisotropicDiffusionImageFilter.h"
#include "itkEuler2DTransform.h"
#include "itkFastMarchingImageFilter.h"
#include "itkGeodesicActiveContourShapePriorLevelSetImageFilter.h"
#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImagePCAShapeModelEstimator.h"
#include "itkMultiplyImageFilter.h"
#include "itkNumericSeriesFileNames.h"
#include "itkNormalVariateGenerator.h"
#include "itkOnePlusOneEvolutionaryOptimizer.h"
#include "itkPCAShapeSignedDistanceFunction.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkShapePriorMAPCostFunction.h"
#include "itkSpatialFunctionImageEvaluatorFilter.h"

// VNL
#include "vnl/vnl_sample.h"

int
main(int argc, char * argv[])
{
  if (argc < 5)
  {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " nbTrain  trainFilePattern";
    std::cerr << " nbModes  modeFilePattern";
    std::cerr << std::endl;
    return 1;
  }

  for (int i = 0; i < argc; i++)
  {
    std::cout << "id: " << i << " arg: " << argv[i] << std::endl;
  }
  constexpr unsigned int Dimension = 2;
  using my_PixelType = float;
  using ImageType = itk::Image<my_PixelType, Dimension>;

  using ReaderType = itk::ImageFileReader<ImageType>;
  using WriterType = itk::ImageFileWriter<ImageType>;
  using ScaleType = itk::MultiplyImageFilter<ImageType, ImageType, ImageType>;

  unsigned int nb_train = atoi(argv[1]);

  itk::NumericSeriesFileNames::Pointer fileNamesCreator = itk::NumericSeriesFileNames::New();
  std::vector<ImageType::Pointer>      trainingImages(nb_train);

  fileNamesCreator->SetStartIndex(0);
  fileNamesCreator->SetEndIndex(nb_train - 1);
  fileNamesCreator->SetSeriesFormat(argv[2]);
  const std::vector<std::string> & shapeModeFileNames = fileNamesCreator->GetFileNames();

  for (unsigned int k = 0; k < nb_train; k++)
  {
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(shapeModeFileNames[k].c_str());
    reader->Update();
    trainingImages[k] = reader->GetOutput();
  }

  using my_Estimatortype = itk::ImagePCAShapeModelEstimator<ImageType, ImageType>;
  my_Estimatortype::Pointer filter = my_Estimatortype::New();
  filter->SetNumberOfTrainingImages(nb_train);
  filter->SetNumberOfPrincipalComponentsRequired(2);

  for (unsigned int k = 0; k < nb_train; k++)
  {
    filter->SetInput(k, trainingImages[k]);
  }

  unsigned int nb_modes = atoi(argv[3]);

  itk::NumericSeriesFileNames::Pointer fileNamesOutCreator = itk::NumericSeriesFileNames::New();

  fileNamesOutCreator->SetStartIndex(0);
  fileNamesOutCreator->SetEndIndex(nb_modes - 1);
  fileNamesOutCreator->SetSeriesFormat(argv[4]);
  const std::vector<std::string> & outFileNames = fileNamesOutCreator->GetFileNames();

  ScaleType::Pointer scaler = ScaleType::New();

  filter->Update();
  my_Estimatortype::VectorOfDoubleType v = filter->GetEigenValues();
  double                               sv_mean = sqrt(v[0]);

  for (unsigned int k = 0; k < nb_modes; k++)
  {
    double sv = sqrt(v[k]);
    double sv_n = sv / sv_mean;
    // double sv_n=sv;
    std::cout << "writing: " << outFileNames[k] << std::endl;

    std::cout << "svd[" << k << "]: " << sv << " norm: " << sv_n << std::endl;
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(outFileNames[k].c_str());
    scaler->SetInput(filter->GetOutput(k));
    scaler->SetConstant(sv_n);
    writer->SetInput(scaler->GetOutput());
    writer->Update();
  }

  return EXIT_SUCCESS;
}
