#ifndef __itkImageFilter_hxx
#define __itkImageFilter_hxx

#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkImageAlgorithm.h"

namespace itk
{

template <class TImage>
void
ImageFilter<TImage>::GenerateData()
{
  typename TImage::ConstPointer input = this->GetInput();
  typename TImage::Pointer      output = this->GetOutput();

  itk::Index<2>              cornerPixel = input->GetLargestPossibleRegion().GetIndex();
  typename TImage::PixelType newValue = 3;

  this->AllocateOutputs();

  ImageAlgorithm::Copy(
    input.GetPointer(), output.GetPointer(), output->GetRequestedRegion(), output->GetRequestedRegion());

  output->SetPixel(cornerPixel, newValue);
}

} // namespace itk


#endif
