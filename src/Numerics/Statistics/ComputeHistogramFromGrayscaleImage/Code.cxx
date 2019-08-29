/*=========================================================================
 *
 *  Copyright Insight Software Consortium
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
#include "itkImageToHistogramFilter.h"
#include "itkImageRandomIteratorWithIndex.h"

int
main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << argv[0] << "InputFileName NumberOfBins" << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;
  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  constexpr unsigned int MeasurementVectorSize = 1; // Grayscale
  const auto             binsPerDimension = static_cast<unsigned int>(std::stoi(argv[2]));

  using ReaderType = itk::ImageFileReader<ImageType>;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(argv[1]);

  ImageType::Pointer image = reader->GetOutput();

  using ImageToHistogramFilterType = itk::Statistics::ImageToHistogramFilter<ImageType>;

  ImageToHistogramFilterType::HistogramType::MeasurementVectorType lowerBound(binsPerDimension);
  lowerBound.Fill(0);

  ImageToHistogramFilterType::HistogramType::MeasurementVectorType upperBound(binsPerDimension);
  upperBound.Fill(255);

  ImageToHistogramFilterType::HistogramType::SizeType size(MeasurementVectorSize);
  size.Fill(binsPerDimension);

  ImageToHistogramFilterType::Pointer imageToHistogramFilter = ImageToHistogramFilterType::New();
  imageToHistogramFilter->SetInput(image);
  imageToHistogramFilter->SetHistogramBinMinimum(lowerBound);
  imageToHistogramFilter->SetHistogramBinMaximum(upperBound);
  imageToHistogramFilter->SetHistogramSize(size);

  try
  {
    imageToHistogramFilter->Update();
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  ImageToHistogramFilterType::HistogramType * histogram = imageToHistogramFilter->GetOutput();

  std::cout << "Frequency = [ ";
  for (unsigned int i = 0; i < histogram->GetSize()[0]; ++i)
  {
    std::cout << histogram->GetFrequency(i);

    if (i != histogram->GetSize()[0] - 1)
    {
      std::cout << "," << std::endl;
    }
  }

  std::cout << " ]" << std::endl;

  return EXIT_SUCCESS;
}
