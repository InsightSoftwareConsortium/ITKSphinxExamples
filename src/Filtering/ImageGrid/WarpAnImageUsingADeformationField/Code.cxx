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

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkVector.h"
#include "itkWarpImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc < 4)
  {
    std::cerr << "Usage: \n" << argv[0] << "<InputFileName> <DisplacementFieldFileName> <OutputFileName>" << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * displacementFieldFileName = argv[2];
  const char * outputFileName = argv[3];

  constexpr unsigned int Dimension = 2;

  using VectorComponentType = float;
  using VectorPixelType = itk::Vector<VectorComponentType, Dimension>;

  using DisplacementFieldType = itk::Image<VectorPixelType, Dimension>;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(inputFileName);

  const auto deformationField = itk::ReadImage<DisplacementFieldType>(displacementFieldFileName);

  using FilterType = itk::WarpImageFilter<ImageType, ImageType, DisplacementFieldType>;

  FilterType::Pointer filter = FilterType::New();

  using InterpolatorType = itk::LinearInterpolateImageFunction<ImageType, double>;

  InterpolatorType::Pointer interpolator = InterpolatorType::New();

  filter->SetInterpolator(interpolator);

  filter->SetOutputSpacing(deformationField->GetSpacing());
  filter->SetOutputOrigin(deformationField->GetOrigin());
  filter->SetOutputDirection(deformationField->GetDirection());

  filter->SetDisplacementField(deformationField);

  filter->SetInput(input);

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
