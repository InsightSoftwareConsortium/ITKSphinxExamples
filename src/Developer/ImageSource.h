#ifndef __itkImageFilter_h
#define __itkImageFilter_h

#include "itkImageToImageFilter.h"

#include <set>

namespace itk
{
template <class TImage>
class ImageSource : public ImageToImageFilter<TImage, TImage>
{
public:
  /** Standard class type alias. */
  using Self = ImageSource;
  using Superclass = ImageToImageFilter<TImage, TImage>;
  using Pointer = SmartPointer<Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImageSource, ImageToImageFilter);

protected:
  ImageSource() {}
  ~ImageSource() {}

  /** Does the real work. */
  virtual void
  GenerateData();

private:
  ImageSource(const Self &); // purposely not implemented
  void
  operator=(const Self &); // purposely not implemented
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "ImageSource.hxx"
#endif


#endif // __itkImageFilter_h
