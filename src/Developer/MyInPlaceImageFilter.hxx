#ifndef __itkMyInPlaceImageFilter_hxx
#define __itkMyInPlaceImageFilter_hxx


#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"

namespace itk
{

template <class TImage>
void
MyInPlaceImageFilter<TImage>::GenerateData()
{
  typename TImage::ConstPointer input = this->GetInput();
  typename TImage::Pointer      output = this->GetOutput();

  // This call must come before the GetRunningInPlace() call or the
  // GetRunningInPlace() will return an incorrect result.
  this->AllocateOutputs();

  if (!this->GetRunningInPlace())
  {
    std::cerr << "The idea of this example is to run inplace, something is wrong!" << std::endl;
    return;
  }

  itk::Index<2>              cornerPixel = input->GetLargestPossibleRegion().GetIndex();
  typename TImage::PixelType newValue = 3;
  output->SetPixel(cornerPixel, newValue);
}

} // namespace itk


#endif
