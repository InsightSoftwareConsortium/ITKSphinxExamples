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
#include "itkExtractImageFilter.h"
#include "itkPasteImageFilter.h"
#include "itkMedianImageFilter.h"

int
main(int argc, char ** argv)
{
  // Verify the number of parameters in the command line
  if (argc <= 3)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " input3DImageFile  output3DImageFile " << std::endl;
    std::cerr << " sliceNumber " << std::endl;
    return EXIT_FAILURE;
  }

  using PixelType = short;
  using ImageType = itk::Image<PixelType, 3>;

  // Here we recover the file names from the command line arguments
  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];

  ImageType::Pointer inputImage;
  try
  {
    inputImage = itk::ReadImage<ImageType>(inputFileName);
  }
  catch (const itk::ExceptionObject & err)
  {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
  }

  using ExtractFilterType = itk::ExtractImageFilter<ImageType, ImageType>;
  auto extractFilter = ExtractFilterType::New();
  extractFilter->SetDirectionCollapseToSubmatrix();

  // set up the extraction region [one slice]
  ImageType::RegionType inputRegion = inputImage->GetBufferedRegion();
  ImageType::SizeType   size = inputRegion.GetSize();
  size[2] = 1; // we extract along z direction
  ImageType::IndexType start = inputRegion.GetIndex();
  const unsigned int   sliceNumber = std::stoi(argv[3]);
  start[2] = sliceNumber;
  ImageType::RegionType desiredRegion;
  desiredRegion.SetSize(size);
  desiredRegion.SetIndex(start);

  extractFilter->SetExtractionRegion(desiredRegion);
  using PasteFilterType = itk::PasteImageFilter<ImageType>;
  auto pasteFilter = PasteFilterType::New();
  using MedianFilterType = itk::MedianImageFilter<ImageType, ImageType>;
  auto medianFilter = MedianFilterType::New();
  extractFilter->SetInput(inputImage);
  medianFilter->SetInput(extractFilter->GetOutput());
  pasteFilter->SetSourceImage(medianFilter->GetOutput());
  pasteFilter->SetDestinationImage(inputImage);
  pasteFilter->SetDestinationIndex(start);

  ImageType::SizeType indexRadius;
  indexRadius[0] = 1; // radius along x
  indexRadius[1] = 1; // radius along y
  indexRadius[2] = 0; // radius along z
  medianFilter->SetRadius(indexRadius);
  medianFilter->UpdateLargestPossibleRegion();
  const ImageType * medianImage = medianFilter->GetOutput();
  pasteFilter->SetSourceRegion(medianImage->GetBufferedRegion());

  try
  {
    itk::WriteImage(pasteFilter->GetOutput(), outputFileName);
  }
  catch (const itk::ExceptionObject & err)
  {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
