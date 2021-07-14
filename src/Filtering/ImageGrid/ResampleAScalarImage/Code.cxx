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
#include "itkResampleImageFilter.h"
#include "itkIdentityTransform.h"

int
main(int argc, char * argv[])
{
  if (argc != 5)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> <size X> <size Y>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  ImageType::SizeType outputSize;

  for (unsigned int dim = 0, k = 3; dim < Dimension; dim++)
  {
    outputSize[dim] = std::stoi(argv[k++]);
  }

  const auto inputImage = itk::ReadImage<ImageType>(inputFileName);

  ImageType::SizeType inputSize = inputImage->GetLargestPossibleRegion().GetSize();
  std::cout << "Input Size: " << inputSize << std::endl;

  ImageType::SpacingType inputSpacing = inputImage->GetSpacing();
  std::cout << "Input Spacing: " << inputSpacing << std::endl;

  ImageType::SpacingType outputSpacing;

  for (unsigned int dim = 0; dim < Dimension; dim++)
  {
    outputSpacing[dim] = static_cast<double>(inputSpacing[dim]) * static_cast<double>(inputSize[dim]) /
                         static_cast<double>(outputSize[dim]);
  }

  std::cout << "Output Size: " << outputSize << std::endl;
  std::cout << "Output Spacing: " << outputSpacing << std::endl;

  using TransformPrecisionType = double;
  using TransformType = itk::IdentityTransform<TransformPrecisionType, Dimension>;
  using FilterType = itk::ResampleImageFilter<ImageType, ImageType>;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(inputImage);
  filter->SetSize(outputSize);
  filter->SetOutputSpacing(outputSpacing);
  filter->SetOutputOrigin(inputImage->GetOrigin());
  filter->SetTransform(TransformType::New());

  try
  {
    itk::WriteImage(filter->GetOutput(), outputFileName);
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
