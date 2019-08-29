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
#include "itkVectorImage.h"
#include "itkNeighborhoodIterator.h"

using VectorImageType = itk::VectorImage<unsigned char, 2>;

int
main(int, char *[])
{
  // Create an image
  VectorImageType::Pointer image = VectorImageType::New();

  itk::Index<2> start;
  start.Fill(0);

  itk::Size<2> size;
  size.Fill(10);

  itk::ImageRegion<2> region(start, size);

  image->SetRegions(region);
  image->SetNumberOfComponentsPerPixel(3);
  image->Allocate();

  // Create the neighborhood iterator
  VectorImageType::SizeType radius;
  radius[0] = 1;
  radius[1] = 1;

  itk::NeighborhoodIterator<VectorImageType> iterator(radius, image, image->GetLargestPossibleRegion());

  while (!iterator.IsAtEnd())
  {
    iterator.GetCenterPixel();

    ++iterator;
  }


  return EXIT_SUCCESS;
}
