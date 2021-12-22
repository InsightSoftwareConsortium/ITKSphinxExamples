#ifndef ImageFilterMultipleInputsDifferentType_h
#define ImageFilterMultipleInputsDifferentType_h

#include "itkImageToImageFilter.h"

namespace itk
{
template <typename TImage, typename TMask>
class ImageFilterMultipleInputsDifferentType : public ImageToImageFilter<TImage, TImage>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ImageFilterMultipleInputsDifferentType);

  /** Standard class type alias. */
  using Self = ImageFilterMultipleInputsDifferentType;
  using Superclass = ImageToImageFilter<TImage, TImage>;
  using Pointer = SmartPointer<Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImageFilterMultipleInputsDifferentType, ImageToImageFilter);

  /** The image to be inpainted in regions where the mask is white.*/
  void
  SetInputImage(const TImage * image);

  /** The mask to be inpainted. White pixels will be inpainted, black pixels will be passed through to the output.*/
  void
  SetInputMask(const TMask * mask);

protected:
  ImageFilterMultipleInputsDifferentType();
  ~ImageFilterMultipleInputsDifferentType() override = default;

  typename TImage::ConstPointer
  GetInputImage();
  typename TMask::ConstPointer
  GetInputMask();

  /** Does the real work. */
  void
  GenerateData() override;
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "ImageFilterMultipleInputsDifferentType.hxx"
#endif


#endif // ImageFilterMultipleInputsDifferentType_h
