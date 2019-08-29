#ifndef __itkImageFilterMultipleOutputsDifferentType_h
#define __itkImageFilterMultipleOutputsDifferentType_h

#include "itkImageToImageFilter.h"

namespace itk
{
template <typename TInputImage, typename TOutputImage1, typename TOutputImage2>
class ImageFilterMultipleOutputsDifferentType
  : public ImageToImageFilter<TInputImage, TOutputImage1> // This doesn't actually matter, as we will be overriding the
                                                          // output image type in MakeOutput()
{
public:
  /** Standard class type alias. */
  using Self = ImageFilterMultipleOutputsDifferentType;
  using Superclass = ImageToImageFilter<TInputImage, TOutputImage1>;
  using Pointer = SmartPointer<Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImageFilterMultipleOutputsDifferentType, ImageToImageFilter);

  TOutputImage1 *
  GetOutput1();
  TOutputImage2 *
  GetOutput2();

protected:
  ImageFilterMultipleOutputsDifferentType();
  ~ImageFilterMultipleOutputsDifferentType() override = default;

  /** Does the real work. */
  void
  GenerateData() override;

  /**  Create the Output */
  DataObject::Pointer
  MakeOutput(ProcessObject::DataObjectPointerArraySizeType idx) override;

private:
  ImageFilterMultipleOutputsDifferentType(const Self &) = delete; // purposely not implemented
  void
  operator=(const Self &) = delete; // purposely not implemented
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "ImageFilterMultipleOutputsDifferentType.hxx"
#endif


#endif // __itkImageFilterMultipleOutputsDifferentType_h
