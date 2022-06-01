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
#include "itkRescaleIntensityImageFilter.h"
#include "itkVectorImage.h"
#include "itkVectorMagnitudeImageFilter.h"

int
main(int argc, char * argv[])
{
  // Verify command line arguments
  if (argc < 3)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " inputImageFile outputImageFile" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse command line arguments
  std::string inputFileName = argv[1];
  std::string outputFileName = argv[2];

  // Setup types
  using VectorImageType = itk::VectorImage<float, 2>;
  using UnsignedCharImageType = itk::Image<unsigned char, 2>;

  const auto input = itk::ReadImage<VectorImageType>(inputFileName);

  using VectorMagnitudeFilterType = itk::VectorMagnitudeImageFilter<VectorImageType, UnsignedCharImageType>;
  auto magnitudeFilter = VectorMagnitudeFilterType::New();
  magnitudeFilter->SetInput(input);

  // To write the magnitude image file, we should rescale the gradient values
  // to a reasonable range
  using rescaleFilterType = itk::RescaleIntensityImageFilter<UnsignedCharImageType, UnsignedCharImageType>;

  auto rescaler = rescaleFilterType::New();
  rescaler->SetOutputMinimum(0);
  rescaler->SetOutputMaximum(255);
  rescaler->SetInput(magnitudeFilter->GetOutput());

  itk::WriteImage(rescaler->GetOutput(), outputFileName);

  return EXIT_SUCCESS;
}
