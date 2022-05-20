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
#include "itkConvolutionImageFilter.h"
#include "itkImageRegionIterator.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

using ImageType = itk::Image<float, 2>;

static void
CreateKernel(ImageType::Pointer kernel, unsigned int width);

int
main(int argc, char * argv[])
{
  // Verify command line arguments
  if (argc < 2)
  {
    std::cerr << "Usage: ";
    std::cerr << argv[0] << "inputImageFile [width]" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse command line arguments
  unsigned int width = 3;
  if (argc > 2)
  {
    width = std::stoi(argv[2]);
  }

  auto kernel = ImageType::New();
  CreateKernel(kernel, width);

  const auto input = itk::ReadImage<ImageType>(argv[1]);

  // Convolve image with kernel.
  using FilterType = itk::ConvolutionImageFilter<ImageType>;
  auto convolutionFilter = FilterType::New();
  convolutionFilter->SetInput(input);
#if ITK_VERSION_MAJOR >= 4
  convolutionFilter->SetKernelImage(kernel);
#else
  convolutionFilter->SetImageKernelInput(kernel);
#endif
#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage<ImageType>(input, true, itksys::SystemTools::GetFilenameName(argv[1]));

  std::stringstream desc;
  desc << "ConvolutionFilter\n"
       << "Kernel Witdh = " << width;
  viewer.AddImage<ImageType>(convolutionFilter->GetOutput(), true, desc.str());
  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}

void
CreateKernel(ImageType::Pointer kernel, unsigned int width)
{
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(width);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  kernel->SetRegions(region);
  kernel->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(kernel, region);

  while (!imageIterator.IsAtEnd())
  {
    // imageIterator.Set(255);
    imageIterator.Set(1);

    ++imageIterator;
  }
}
