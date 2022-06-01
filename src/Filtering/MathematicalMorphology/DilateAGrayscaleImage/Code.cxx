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
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkFlatStructuringElement.h"
#include "itkGrayscaleDilateImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc < 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " <inputImage> <outputImage> <radius>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }
  const char *       inputImage = argv[1];
  const char *       outputImage = argv[2];
  const unsigned int radiusValue = std::stoi(argv[3]);

  using PixelType = unsigned char;
  constexpr unsigned int Dimension = 2;

  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(inputImage);

  using StructuringElementType = itk::FlatStructuringElement<Dimension>;
  StructuringElementType::RadiusType radius;
  radius.Fill(radiusValue);
  StructuringElementType structuringElement = StructuringElementType::Ball(radius);

  using GrayscaleDilateImageFilterType = itk::GrayscaleDilateImageFilter<ImageType, ImageType, StructuringElementType>;

  auto dilateFilter = GrayscaleDilateImageFilterType::New();
  dilateFilter->SetInput(input);
  dilateFilter->SetKernel(structuringElement);

  try
  {
    itk::WriteImage(dilateFilter->GetOutput(), outputImage);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
