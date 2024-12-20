#ifndef ImageFilterMultipleOutputsDifferentType_h
#define ImageFilterMultipleOutputsDifferentType_h

#include "itkImageToImageFilter.h"

namespace itk
{
template <typename TInputImage, typename TOutputImage1, typename TOutputImage2>
class ImageFilterMultipleOutputsDifferentType
  : public ImageToImageFilter<TInputImage, TOutputImage1> // This doesn't actually matter, as we will be overriding the
                                                          // output image type in MakeOutput()
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ImageFilterMultipleOutputsDifferentType);

  /** Standard class type alias. */
  using Self = ImageFilterMultipleOutputsDifferentType;
  using Superclass = ImageToImageFilter<TInputImage, TOutputImage1>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(ImageFilterMultipleOutputsDifferentType);

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
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "ImageFilterMultipleOutputsDifferentType.hxx"
#endif


#endif // ImageFilterMultipleOutputsDifferentType_h
