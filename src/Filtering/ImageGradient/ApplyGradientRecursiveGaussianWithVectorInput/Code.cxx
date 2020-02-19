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
#include "itkImage.h"
#include "itkGradientRecursiveGaussianImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkVectorIndexSelectionCastImageFilter.h"
#include "itkVectorMagnitudeImageFilter.h"
#include "itkInvertIntensityImageFilter.h"
#include "itkComposeImageFilter.h"
#include "itkCastImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 6)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <OutputFileName1X> <OutputFileName1Y> <OutputFileName2X> <OutputFileName2Y>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * outputFileName1X = argv[2];
  const char * outputFileName1Y = argv[3];
  const char * outputFileName2X = argv[4];
  const char * outputFileName2Y = argv[5];

  const char * filenames[4];
  filenames[0] = outputFileName1X;
  filenames[1] = outputFileName1Y;
  filenames[2] = outputFileName2X;
  filenames[3] = outputFileName2Y;

  constexpr unsigned int ImageDimension = 2;
  constexpr unsigned int VectorDimension = 2;
  constexpr unsigned int CovDimension = 4;

  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, ImageDimension>;
  using DoublePixelType = double;
  using DoubleImageType = itk::Image<DoublePixelType, ImageDimension>;
  using VecPixelType = itk::Vector<DoublePixelType, VectorDimension>;
  using VecImageType = itk::Image<VecPixelType, ImageDimension>;
  using CovPixelType = itk::CovariantVector<DoublePixelType, CovDimension>;
  using CovImageType = itk::Image<CovPixelType, ImageDimension>;

  using ReaderType = itk::ImageFileReader<ImageType>;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(inputFileName);

  // Invert the input image
  using InvertType = itk::InvertIntensityImageFilter<ImageType, ImageType>;
  InvertType::Pointer inverter = InvertType::New();
  inverter->SetInput(reader->GetOutput());

  // Cast the image to double type.
  using CasterType = itk::CastImageFilter<ImageType, DoubleImageType>;
  CasterType::Pointer caster = CasterType::New();
  CasterType::Pointer caster2 = CasterType::New();

  // Create an image, were each pixel has 2 values: first value is the value
  // coming from the input image, second value is coming from the inverted
  // image
  using ComposeType = itk::ComposeImageFilter<DoubleImageType, VecImageType>;
  ComposeType::Pointer composer = ComposeType::New();
  caster->SetInput(reader->GetOutput());
  composer->SetInput(0, caster->GetOutput());
  caster2->SetInput(inverter->GetOutput());
  composer->SetInput(1, caster2->GetOutput());

  // Apply the gradient filter on the two images, this will return and image
  // with 4 values per pixel: two X and Y gradients
  using FilterType = itk::GradientRecursiveGaussianImageFilter<VecImageType, CovImageType>;
  FilterType::Pointer filter = FilterType::New();
  filter->SetInput(composer->GetOutput());

  // Set up the filter to select each gradient
  using IndexSelectionType = itk::VectorIndexSelectionCastImageFilter<CovImageType, DoubleImageType>;
  IndexSelectionType::Pointer indexSelectionFilter = IndexSelectionType::New();
  indexSelectionFilter->SetInput(filter->GetOutput());

  // Rescale for png output
  using RescalerType = itk::RescaleIntensityImageFilter<DoubleImageType, ImageType>;
  RescalerType::Pointer rescaler = RescalerType::New();
  rescaler->SetOutputMinimum(itk::NumericTraits<PixelType>::min());
  rescaler->SetOutputMaximum(itk::NumericTraits<PixelType>::max());
  rescaler->SetInput(indexSelectionFilter->GetOutput());

  using WriterType = itk::ImageFileWriter<ImageType>;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput(rescaler->GetOutput());

  // Write the X and Y images
  for (int i = 0; i < 4; ++i)
  {
    indexSelectionFilter->SetIndex(i);
    writer->SetFileName(filenames[i]);

    try
    {
      writer->Update();
    }
    catch (itk::ExceptionObject & error)
    {
      std::cerr << "Error: " << error << std::endl;
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
