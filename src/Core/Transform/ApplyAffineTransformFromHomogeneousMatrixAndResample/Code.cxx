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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkAffineTransform.h"
#include "itkResampleImageFilter.h"
#include "itkWindowedSincInterpolateImageFunction.h"

int
main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> <DefaultPixelValue>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;
  using ScalarType = double;

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];
  const auto   defaultValue = static_cast<ScalarType>(std::stod(argv[3]));

  using MatrixType = itk::Matrix<ScalarType, Dimension + 1, Dimension + 1>;
  MatrixType matrix;
  matrix[0][0] = std::cos(0.05);
  matrix[0][1] = std::sin(0.05);
  matrix[0][2] = 0.;

  matrix[1][0] = -matrix[0][1];
  matrix[1][1] = matrix[0][0];
  matrix[1][2] = 0.;

  matrix[2][0] = -10.;
  matrix[2][1] = -20.;
  matrix[2][2] = 1.;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(inputFileName);

  const ImageType::SizeType & size = input->GetLargestPossibleRegion().GetSize();

  using ResampleImageFilterType = itk::ResampleImageFilter<ImageType, ImageType>;
  auto resample = ResampleImageFilterType::New();
  resample->SetInput(input);
  resample->SetReferenceImage(input);
  resample->UseReferenceImageOn();
  resample->SetSize(size);
  resample->SetDefaultPixelValue(defaultValue);

  constexpr unsigned int Radius = 3;
  using InterpolatorType = itk::WindowedSincInterpolateImageFunction<ImageType, Radius>;
  auto interpolator = InterpolatorType::New();

  resample->SetInterpolator(interpolator);

  using TransformType = itk::AffineTransform<ScalarType, Dimension>;
  auto transform = TransformType::New();

  // get transform parameters from MatrixType
  TransformType::ParametersType parameters(Dimension * Dimension + Dimension);
  for (unsigned int i = 0; i < Dimension; ++i)
  {
    for (unsigned int j = 0; j < Dimension; ++j)
    {
      parameters[i * Dimension + j] = matrix[i][j];
    }
  }
  for (unsigned int i = 0; i < Dimension; ++i)
  {
    parameters[i + Dimension * Dimension] = matrix[i][Dimension];
  }
  transform->SetParameters(parameters);

  resample->SetTransform(transform);

  try
  {
    itk::WriteImage(resample->GetOutput(), outputFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
