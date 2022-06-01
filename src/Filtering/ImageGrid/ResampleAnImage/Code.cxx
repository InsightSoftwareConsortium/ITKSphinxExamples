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
#include "itkLinearInterpolateImageFunction.h"
#include "itkResampleImageFilter.h"
#include "itkScaleTransform.h"

int
main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> <scale>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];
  const float  scale = std::stod(argv[3]);

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;
  using ScalarType = double;
  using IndexValueType = typename itk::Index<Dimension>::IndexValueType;

  const typename ImageType::Pointer     inputImage = itk::ReadImage<ImageType>(inputFileName);
  const typename ImageType::RegionType  inputRegion = inputImage->GetLargestPossibleRegion();
  const typename ImageType::SizeType    inputSize = inputRegion.GetSize();
  const typename ImageType::SpacingType inputSpacing = inputImage->GetSpacing();
  const typename ImageType::PointType   inputOrigin = inputImage->GetOrigin();

  /*
   * We will scale the objects in the image by the factor `scale`; that is they
   * will be shrunk (scale < 1.0) or enlarged (scale > 1.0).  However, the
   * number of pixels for each dimension of the output image will equal the
   * corresponding number of pixels in the input image, with padding (if
   * shrunk) or cropping (if enlarged) as necessary.  Furthermore, the physical
   * distance between adjacent pixels will be the same in the input and the
   * output images.  In contrast, if you want to change the resolution of the
   * image without changing the represented physical size of the objects in the
   * image, omit the transform and instead use:
   *
   *   outputSize[d] = inputSize[d] * scale;
   *   outputSpacing[d] = inputSpacing[d] / scale;
   *   outputOrigin[d] = inputOrigin[d] + 0.5 * (outputSpacing[d] - inputSpacing[d]);
   *
   * in the loop over dimensions.
   */

  typename ImageType::SizeType    outputSize = inputSize;
  typename ImageType::SpacingType outputSpacing = inputSpacing;
  typename ImageType::PointType   outputOrigin = inputOrigin;

  using ScaleTransformType = itk::ScaleTransform<ScalarType, Dimension>;
  auto scaleTransform = ScaleTransformType::New();

  typename ScaleTransformType::ParametersType scaleTransformParameters = scaleTransform->GetParameters();
  itk::Point<ScalarType, Dimension>           scaleTransformCenter;
  for (unsigned int d = 0; d < Dimension; ++d)
  {
    scaleTransformParameters[d] = scale;
    scaleTransformCenter[d] = static_cast<ScalarType>(static_cast<IndexValueType>(inputSize[d] / 2));
  }
  scaleTransform->SetParameters(scaleTransformParameters);
  scaleTransform->SetCenter(scaleTransformCenter);

  using LinearInterpolatorType = itk::LinearInterpolateImageFunction<ImageType, ScalarType>;
  auto interpolator = LinearInterpolatorType::New();

  using ResampleFilterType = itk::ResampleImageFilter<ImageType, ImageType>;
  auto resampleFilter = ResampleFilterType::New();

  resampleFilter->SetInput(inputImage);
  resampleFilter->SetTransform(scaleTransform);
  resampleFilter->SetInterpolator(interpolator);
  resampleFilter->SetSize(outputSize);
  resampleFilter->SetOutputSpacing(outputSpacing);
  resampleFilter->SetOutputOrigin(outputOrigin);

  try
  {
    itk::WriteImage(resampleFilter->GetOutput(), outputFileName);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
