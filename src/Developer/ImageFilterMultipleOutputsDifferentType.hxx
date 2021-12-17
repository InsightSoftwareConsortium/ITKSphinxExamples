#ifndef __itkImageFilterMultipleOutputsDifferentType_hxx
#define __itkImageFilterMultipleOutputsDifferentType_hxx


#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"

namespace itk
{

template <typename TInputImage, typename TOutputImage1, typename TOutputImage2>
ImageFilterMultipleOutputsDifferentType<TInputImage, TOutputImage1, TOutputImage2>::
  ImageFilterMultipleOutputsDifferentType()
{
  this->SetNumberOfRequiredOutputs(2);
  this->SetNumberOfRequiredInputs(0);

  this->SetNthOutput(0, this->MakeOutput(0));
  this->SetNthOutput(1, this->MakeOutput(1));
}

template <typename TInputImage, typename TOutputImage1, typename TOutputImage2>
void
ImageFilterMultipleOutputsDifferentType<TInputImage, TOutputImage1, TOutputImage2>::GenerateData()
{
  itk::Index<2> start;
  start.Fill(0);

  itk::Size<2> size;
  size.Fill(20);

  itk::ImageRegion<2> region(start, size);

  // Setup output 1
  typename TOutputImage1::Pointer output1 = this->GetOutput1();
  output1->SetRegions(region);
  output1->Allocate();

  // Setup output 2
  typename TOutputImage2::Pointer output2 = this->GetOutput2();
  output2->SetRegions(region);
  output2->Allocate();
}

template <typename TInputImage, typename TOutputImage1, typename TOutputImage2>
DataObject::Pointer
ImageFilterMultipleOutputsDifferentType<TInputImage, TOutputImage1, TOutputImage2>::MakeOutput(
  ProcessObject::DataObjectPointerArraySizeType idx)
{
  DataObject::Pointer output;

  switch (idx)
  {
    case 0:
      output = (TOutputImage1::New()).GetPointer();
      break;
    case 1:
      output = (TOutputImage2::New()).GetPointer();
      break;
    default:
      std::cerr << "No output " << idx << std::endl;
      output = nullptr;
      break;
  }
  return output.GetPointer();
}

template <typename TInputImage, typename TOutputImage1, typename TOutputImage2>
TOutputImage1 *
ImageFilterMultipleOutputsDifferentType<TInputImage, TOutputImage1, TOutputImage2>::GetOutput1()
{
  return dynamic_cast<TOutputImage1 *>(this->ProcessObject::GetOutput(0));
}

template <typename TInputImage, typename TOutputImage1, typename TOutputImage2>
TOutputImage2 *
ImageFilterMultipleOutputsDifferentType<TInputImage, TOutputImage1, TOutputImage2>::GetOutput2()
{
  return dynamic_cast<TOutputImage2 *>(this->ProcessObject::GetOutput(1));
}

} // namespace itk


#endif
