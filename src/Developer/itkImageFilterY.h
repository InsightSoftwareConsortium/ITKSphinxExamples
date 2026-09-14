#ifndef itkImageFilterY_h
#define itkImageFilterY_h

#include "itkImageToImageFilter.h"

#include "itkRecursiveGaussianImageFilter.h"

namespace itk
{
template <typename TImage>
class ImageFilterY : public ImageToImageFilter<TImage, TImage>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ImageFilterY);

  /** Standard class type alias. */
  using Self = ImageFilterY;
  using Superclass = ImageToImageFilter<TImage, TImage>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkOverrideGetNameOfClassMacro(ImageFilterY);


  /** Image dimension. */
  static constexpr unsigned int ImageDimension = TImage::ImageDimension;


  /**  Smoothing filter type */
  using InternalGaussianFilterType = RecursiveGaussianImageFilter<TImage, TImage>;

  /**  Pointer to a gaussian filter.  */
  using InternalGaussianFilterPointer = typename InternalGaussianFilterType::Pointer;

protected:
  ImageFilterY() = default;
  ~ImageFilterY() override = default;

  /** Does the real work. */
  void
  GenerateData() override;
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkImageFilterY.hxx"
#endif


#endif // itkImageFilterY_h
