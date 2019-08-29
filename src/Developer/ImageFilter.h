#ifndef __itkImageFilter_h
#define __itkImageFilter_h

#include "itkImageToImageFilter.h"

namespace itk
{
template <class TImage>
class ImageFilter : public ImageToImageFilter<TImage, TImage>
{
public:
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

private:
  ImageFilter(const Self &) = delete; // purposely not implemented
  void
  operator=(const Self &) = delete; // purposely not implemented
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "ImageFilter.hxx"
#endif


#endif // __itkImageFilter_h
