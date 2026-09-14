#ifndef itkImageFilterX_h
#define itkImageFilterX_h

#include "itkImageToImageFilter.h"

namespace itk
{
template <typename TImage>
class ImageFilterX : public ImageToImageFilter<TImage, TImage>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ImageFilterX);

  /** Standard class type alias. */
  using Self = ImageFilterX;
  using Superclass = ImageToImageFilter<TImage, TImage>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(ImageFilterX);

  itkSetMacro(Variable, double);
  itkGetMacro(Variable, double);

protected:
  ImageFilterX() = default;
  ~ImageFilterX() override = default;

  /** Does the real work. */
  void
  GenerateData() override;

  double m_Variable;
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkImageFilterX.hxx"
#endif


#endif // itkImageFilterX_h
