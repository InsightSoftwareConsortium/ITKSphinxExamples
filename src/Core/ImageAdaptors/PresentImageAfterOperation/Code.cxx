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
#include "itkImageAdaptor.h"
#include "itkImageRegionIterator.h"

using ScalarImageType = itk::Image<float, 2>;
using VectorImageType = itk::Image<itk::CovariantVector<float, 3>, 2>;


static void
CreateImage(VectorImageType::Pointer image);

class VectorPixelAccessor
{
public:
  using InternalType = itk::CovariantVector<float, 3>;
  using ExternalType = float;

  void
  operator=(const VectorPixelAccessor & vpa)
  {
    m_Index = vpa.m_Index;
  }
  ExternalType
  Get(const InternalType & input) const
  {
    return static_cast<ExternalType>(input[m_Index]);
  }
  void
  SetIndex(unsigned int index)
  {
    m_Index = index;
  }

private:
  unsigned int m_Index;
};

int
main(int, char *[])
{
  VectorImageType::Pointer image = VectorImageType::New();
  CreateImage(image);

  itk::Index<2> index;
  index.Fill(0);

  std::cout << image->GetPixel(index) << std::endl;

  using ImageAdaptorType = itk::ImageAdaptor<VectorImageType, VectorPixelAccessor>;

  ImageAdaptorType::Pointer adaptor = ImageAdaptorType::New();

  VectorPixelAccessor accessor;
  accessor.SetIndex(0);
  adaptor->SetPixelAccessor(accessor);
  adaptor->SetImage(image);

  std::cout << adaptor->GetPixel(index) << std::endl;

  return EXIT_SUCCESS;
}

void
CreateImage(VectorImageType::Pointer image)
{
  VectorImageType::IndexType start;
  start.Fill(0);

  VectorImageType::SizeType size;
  size.Fill(2);

  VectorImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<VectorImageType> imageIterator(image, image->GetLargestPossibleRegion());
  itk::CovariantVector<float, 3>            vec;
  vec[0] = 1;
  vec[1] = 2;
  vec[2] = 3;

  while (!imageIterator.IsAtEnd())
  {
    imageIterator.Set(vec);

    ++imageIterator;
  }
}
