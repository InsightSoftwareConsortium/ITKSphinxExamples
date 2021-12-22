#ifndef ImageFilterX_h
#define ImageFilterX_h

#include "itkImageToImageFilter.h"

namespace itk
{
template <typename TImage>
class ImageFilter : public ImageToImageFilter<TImage, TImage>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ImageFilter);

  /** Standard class type alias. */
  using Self = ImageFilter;
  using Superclass = ImageToImageFilter<TImage, TImage>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImageFilter, ImageToImageFilter);

  itkSetMacro(Variable, double);
  itkGetMacro(Variable, double);

protected:
  ImageFilter() = default;
  ~ImageFilter() override = default;

  /** Does the real work. */
  void
  GenerateData() override;

  double m_Variable;
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "ImageFilterX.hxx"
#endif


#endif // __ImageFilterX_h
