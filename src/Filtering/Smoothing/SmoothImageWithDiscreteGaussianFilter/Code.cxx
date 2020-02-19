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
#include "itkDiscreteGaussianImageFilter.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

int
main(int argc, char * argv[])
{
  // Verify command line arguments
  if (argc < 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " inputImageFile [variance]" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse command line argumentsa
  std::string inputFilename = argv[1];

  double variance = 4.0;
  if (argc > 2)
  {
    variance = std::stod(argv[2]);
  }

  // Setup types
  using UnsignedCharImageType = itk::Image<unsigned char, 2>;
  using FloatImageType = itk::Image<float, 2>;

  using readerType = itk::ImageFileReader<UnsignedCharImageType>;

  using filterType = itk::DiscreteGaussianImageFilter<UnsignedCharImageType, FloatImageType>;

  // Create and setup a reader
  readerType::Pointer reader = readerType::New();
  reader->SetFileName(inputFilename.c_str());

  // Create and setup a Gaussian filter
  filterType::Pointer gaussianFilter = filterType::New();
  gaussianFilter->SetInput(reader->GetOutput());
  gaussianFilter->SetVariance(variance);

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage<UnsignedCharImageType>(reader->GetOutput());
  viewer.AddImage<FloatImageType>(gaussianFilter->GetOutput());
  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}
