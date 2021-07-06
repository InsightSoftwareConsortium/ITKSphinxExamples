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
#include "itkTranslationTransform.h"
#include "itkResampleImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 5)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> <translation X> <translation Y>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  constexpr unsigned int Dimension = 2;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(inputFileName);

  using TransformType = itk::TranslationTransform<double, Dimension>;

  TransformType::OutputVectorType vector;
  vector[0] = std::stod(argv[3]);
  vector[1] = std::stod(argv[4]);

  TransformType::Pointer translation = TransformType::New();
  translation->Translate(vector);

  using ResampleImageFilterType = itk::ResampleImageFilter<ImageType, ImageType>;
  ResampleImageFilterType::Pointer resampleFilter = ResampleImageFilterType::New();
  resampleFilter->SetTransform(translation.GetPointer());
  resampleFilter->SetInput(input);
  resampleFilter->SetSize(input->GetLargestPossibleRegion().GetSize());

  try
  {
    itk::WriteImage(resampleFilter->GetOutput(), outputFileName);
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
