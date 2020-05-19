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
#include "itkAdditiveGaussianNoiseImageFilter.h"

int
main(int argc, char * argv[])
{
  // Check for proper arguments; if not, explain usage.
  if (argc != 5)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> [Mean] [Standard Deviation]";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  // Initialize and assign user provided variables
  const char * inputImage = argv[1];
  const char * outputImage = argv[2];

  // Get floating point numbers for the mean and std dev to perform the algorithm
  const double mean = std::stod(argv[3]);
  const double deviation = std::stod(argv[4]);

  constexpr unsigned int Dimension = 2;
  // Use unsigned char to save to PNG format
  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  // Read the file to be converted
  using ReaderType = itk::ImageFileReader<ImageType>;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(inputImage);

  using ImageType = itk::Image<PixelType, Dimension>;

  // Create the filter and apply the algorithm to the image
  using FilterType = itk::AdditiveGaussianNoiseImageFilter<ImageType, ImageType>;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(reader->GetOutput());
  filter->SetMean(mean);                   // Set the mean
  filter->SetStandardDeviation(deviation); // Set the standard deviation

  // Set the writer to save file
  using WriterType = itk::ImageFileWriter<ImageType>;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(outputImage);
  writer->SetInput(filter->GetOutput());

  // Write the output image
  try
  {
    writer->Update();
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
