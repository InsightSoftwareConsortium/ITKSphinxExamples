#ifndef __MultiThreadedImageFilter_hxx
#define __MultiThreadedImageFilter_hxx


#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"

namespace itk
{

template <class TImage>
void
MultiThreadedImageFilter<TImage>::DynamicThreadedGenerateData(const OutputImageRegionType & region)
{
  typename TImage::ConstPointer input = this->GetInput();
  typename TImage::Pointer      output = this->GetOutput();

  ImageAlgorithm::Copy(input.GetPointer(), output.GetPointer(), region, region);

  itk::Index<2> cornerPixel = region.GetIndex();
  std::cout << "cornerPixel: " << cornerPixel << std::endl;
  typename TImage::PixelType newValue = 3;

  output->SetPixel(cornerPixel, newValue);
}

} // namespace itk


#endif
