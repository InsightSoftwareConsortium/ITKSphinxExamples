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
#include "itkNeighborhoodOperatorImageFunction.h"
#include "itkNeighborhoodOperator.h"

using UnsignedCharImageType = itk::Image<unsigned char, 2>;

static void
CreateImage(UnsignedCharImageType::Pointer image);

int
main()
{
  auto image = UnsignedCharImageType::New();
  CreateImage(image);

  itk::Neighborhood<float, 2> neighborhood;
  neighborhood.SetRadius(1);
  for (unsigned int i = 0; i < neighborhood.GetSize()[0] * neighborhood.GetSize()[1]; ++i)
  {
    neighborhood[i] = 1;
  }

  using NeighborhoodOperatorImageFunctionType = itk::NeighborhoodOperatorImageFunction<UnsignedCharImageType, float>;
  NeighborhoodOperatorImageFunctionType::Pointer neighborhoodOperatorImageFunction =
    NeighborhoodOperatorImageFunctionType::New();
  neighborhoodOperatorImageFunction->SetOperator(neighborhood);
  neighborhoodOperatorImageFunction->SetInputImage(image);

  {
    itk::Index<2> index;
    index.Fill(20);

    float output = neighborhoodOperatorImageFunction->EvaluateAtIndex(index);
    std::cout << "Sum on border: " << output << std::endl;
  }

  {
    itk::Index<2> index;
    index.Fill(35);

    float output = neighborhoodOperatorImageFunction->EvaluateAtIndex(index);
    std::cout << "Sum in center: " << output << std::endl;
  }

  {
    itk::Index<2> index;
    index.Fill(7);

    float output = neighborhoodOperatorImageFunction->EvaluateAtIndex(index);
    std::cout << "Sum outside: " << output << std::endl;
  }

  return EXIT_SUCCESS;
}

void
CreateImage(UnsignedCharImageType::Pointer image)
{
  // Create an image with 2 connected components
  UnsignedCharImageType::IndexType start;
  start.Fill(0);

  UnsignedCharImageType::SizeType size;
  size.Fill(100);

  UnsignedCharImageType::RegionType region(start, size);

  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);

  // Make a square
  for (unsigned int r = 20; r < 80; ++r)
  {
    for (unsigned int c = 20; c < 80; ++c)
    {
      UnsignedCharImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 1);
    }
  }
}
