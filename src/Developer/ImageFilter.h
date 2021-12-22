#ifndef __ImageFilter_h
#define __ImageFilter_h

#include "itkImageToImageFilter.h"

namespace itk
{
template <class TImage>
class ImageFilter : public ImageToImageFilter<TImage, TImage>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ImageFilter);
  /** Standard class type alias. */
  using Self = ImageFilter;
  using Superclass = ImageToImageFilter<TImage, TImage>;
  using Pointer = SmartPointer<Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImageFilter, ImageToImageFilter);

protected:
  ImageFilter() = default;
  ~ImageFilter() override = default;

  /** Does the real work. */
  void
  GenerateData() override;
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "ImageFilter.hxx"
#endif


#endif // __ImageFilter_h
