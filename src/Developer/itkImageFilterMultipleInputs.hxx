#ifndef itkImageFilterMultipleInputs_hxx
#define itkImageFilterMultipleInputs_hxx


#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"

namespace itk
{

template <typename TImage>
ImageFilterMultipleInputs<TImage>::ImageFilterMultipleInputs()
{
  this->SetNumberOfRequiredInputs(2);
}

template <typename TImage>
void
ImageFilterMultipleInputs<TImage>::SetInputImage(const TImage * image)
{
  this->SetNthInput(0, const_cast<TImage *>(image));
}

template <typename TImage>
void
ImageFilterMultipleInputs<TImage>::SetInputMask(const TImage * mask)
{
  this->SetNthInput(1, const_cast<TImage *>(mask));
}

template <typename TImage>
void
ImageFilterMultipleInputs<TImage>::GenerateData()
{
  typename TImage::ConstPointer input = this->GetInput();

  typename TImage::Pointer output = this->GetOutput();
  output->SetRegions(input->GetLargestPossibleRegion());
  output->Allocate();

  itk::ImageRegionIterator<TImage>      outputIterator(output, output->GetLargestPossibleRegion());
  itk::ImageRegionConstIterator<TImage> inputIterator(input, input->GetLargestPossibleRegion());

  while (!outputIterator.IsAtEnd())
  {
    if (inputIterator.GetIndex()[0] == inputIterator.GetIndex()[1])
    {
      outputIterator.Set(255);
    }
    else
    {
      outputIterator.Set(inputIterator.Get());
    }

    ++inputIterator;
    ++outputIterator;
  }
}

} // namespace itk


#endif
