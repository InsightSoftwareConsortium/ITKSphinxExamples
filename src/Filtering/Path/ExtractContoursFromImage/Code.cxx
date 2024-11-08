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
#include "itkImageFileWriter.h"
#include "itkContourExtractor2DImageFilter.h"
#include "itkApproximateSignedDistanceMapImageFilter.h"

using UnsignedCharImageType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;

static void
CreateImage(UnsignedCharImageType::Pointer image);

int
main()
{
  auto image = UnsignedCharImageType::New();
  CreateImage(image);

  using ApproximateSignedDistanceMapImageFilterType =
    itk::ApproximateSignedDistanceMapImageFilter<UnsignedCharImageType, FloatImageType>;
  ApproximateSignedDistanceMapImageFilterType::Pointer approximateSignedDistanceMapImageFilter =
    ApproximateSignedDistanceMapImageFilterType::New();
  approximateSignedDistanceMapImageFilter->SetInput(image);
  approximateSignedDistanceMapImageFilter->SetInsideValue(255);
  approximateSignedDistanceMapImageFilter->SetOutsideValue(0);
  approximateSignedDistanceMapImageFilter->Update();

  using ContourExtractor2DImageFilterType = itk::ContourExtractor2DImageFilter<FloatImageType>;
  auto contourExtractor2DImageFilter = ContourExtractor2DImageFilterType::New();
  contourExtractor2DImageFilter->SetInput(approximateSignedDistanceMapImageFilter->GetOutput());
  contourExtractor2DImageFilter->SetContourValue(0);
  contourExtractor2DImageFilter->Update();

  std::cout << "There are " << contourExtractor2DImageFilter->GetNumberOfOutputs() << " contours" << std::endl;


  for (unsigned int i = 0; i < contourExtractor2DImageFilter->GetNumberOfOutputs(); ++i)
  {
    std::cout << "Contour " << i << ": " << std::endl;
    ContourExtractor2DImageFilterType::VertexListType::ConstIterator vertexIterator =
      contourExtractor2DImageFilter->GetOutput(i)->GetVertexList()->Begin();
    while (vertexIterator != contourExtractor2DImageFilter->GetOutput(i)->GetVertexList()->End())
    {
      std::cout << vertexIterator->Value() << std::endl;
      ++vertexIterator;
    }
    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}

void
CreateImage(UnsignedCharImageType::Pointer image)
{
  // Create an image
  itk::Index<2> start{};

  itk::Size<2> size;
  size.Fill(100);

  itk::ImageRegion<2> region(start, size);
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  // Create a line of white pixels
  for (unsigned int i = 40; i < 60; ++i)
  {
    itk::Index<2> pixel;
    pixel.Fill(i);
    image->SetPixel(pixel, 255);
  }

  // Create another line of pixels
  for (unsigned int i = 10; i < 20; ++i)
  {
    itk::Index<2> pixel;
    pixel[0] = 10;
    pixel[1] = i;
    image->SetPixel(pixel, 255);
  }

  itk::WriteImage(image, "image.png");
}
