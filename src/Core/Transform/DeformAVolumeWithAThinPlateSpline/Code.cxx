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
#include "itkImageFileWriter.h"
#include "itkImage.h"
#include "itkResampleImageFilter.h"
#include "itkThinPlateSplineKernelTransform.h"
#include "itkPointSet.h"
#include "itkMesh.h"
#include "itkMeshFileReader.h"
#include "itkCheckerBoardImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 6)
  {
    std::cerr << "Usage: " << argv[0];
    std::cerr << " <SourceLandmarks>";
    std::cerr << " <TargetLandmarks>";
    std::cerr << " <InputImage>";
    std::cerr << " <DeformedImage>";
    std::cerr << " <CheckerBoardImage>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }
  const char * sourceLandmarksFile = argv[1];
  const char * targetLandmarksFile = argv[2];
  const char * inputImageFile = argv[3];
  const char * deformedImageFile = argv[4];
  const char * checkerboardImageFile = argv[5];

  constexpr unsigned int Dimension = 3;
  using CoordinateRepType = double;

  using TransformType = itk::ThinPlateSplineKernelTransform<CoordinateRepType, Dimension>;
  using PointSetType = TransformType::PointSetType;

  using PixelType = unsigned char;
  using MeshType = itk::Mesh<PointSetType::PixelType, Dimension, PointSetType::MeshTraits>;
  using ImageType = itk::Image<PixelType, Dimension>;

  auto               sourceLandmarks = PointSetType::New();
  auto               targetLandmarks = PointSetType::New();
  ImageType::Pointer inputImage;
  try
  {
    auto sourceLandmarksMesh = itk::ReadMesh<MeshType>(sourceLandmarksFile);
    sourceLandmarks->SetPoints(sourceLandmarksMesh->GetPoints());

    auto targetLandmarksMesh = itk::ReadMesh<MeshType>(targetLandmarksFile);
    targetLandmarks->SetPoints(targetLandmarksMesh->GetPoints());

    inputImage = itk::ReadImage<ImageType>(inputImageFile);
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  using TransformType = itk::ThinPlateSplineKernelTransform<CoordinateRepType, Dimension>;

  auto thinPlateSpline = TransformType::New();
  thinPlateSpline->SetSourceLandmarks(sourceLandmarks);
  thinPlateSpline->SetTargetLandmarks(targetLandmarks);
  thinPlateSpline->ComputeWMatrix();

  using ResamplerType = itk::ResampleImageFilter<ImageType, ImageType>;
  auto resampler = ResamplerType::New();

  resampler->SetInput(inputImage);

  using InterpolatorType = itk::LinearInterpolateImageFunction<ImageType, CoordinateRepType>;
  auto interpolator = InterpolatorType::New();
  resampler->SetInterpolator(interpolator);

  resampler->SetUseReferenceImage(true);
  resampler->SetReferenceImage(inputImage);

  resampler->SetTransform(thinPlateSpline);

  using CheckerBoardFilterType = itk::CheckerBoardImageFilter<ImageType>;
  auto checkerboardFilter = CheckerBoardFilterType::New();
  checkerboardFilter->SetInput1(inputImage);
  checkerboardFilter->SetInput2(resampler->GetOutput());

  try
  {
    resampler->Update();
    checkerboardFilter->Update();

    itk::WriteImage(resampler->GetOutput(), deformedImageFile);
    itk::WriteImage(checkerboardFilter->GetOutput(), checkerboardImageFile);
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
