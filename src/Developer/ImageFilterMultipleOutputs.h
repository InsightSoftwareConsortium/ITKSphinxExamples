#ifndef ImageFilterMultipleOutputs_h
#define ImageFilterMultipleOutputs_h

#include "itkImageToImageFilter.h"

namespace itk
{
template <typename TImage>
class ImageFilterMultipleOutputs : public ImageToImageFilter<TImage, TImage>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ImageFilterMultipleOutputs);
  /** Standard class type alias. */
  using Self = ImageFilterMultipleOutputs;
  using Superclass = ImageToImageFilter<TImage, TImage>;
  using Pointer = SmartPointer<Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImageFilterMultipleOutputs, ImageToImageFilter);

  TImage *
  GetOutput1();
  TImage *
  GetOutput2();

protected:
  ImageFilterMultipleOutputs();
  ~ImageFilterMultipleOutputs() override = default;

  /** Does the real work. */
  void
  GenerateData() override;

  /**  Create the Output */
  DataObject::Pointer
  MakeOutput(ProcessObject::DataObjectPointerArraySizeType idx) override;
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "ImageFilterMultipleOutputs.hxx"
#endif


#endif // ImageFilterMultipleOutputs_h
