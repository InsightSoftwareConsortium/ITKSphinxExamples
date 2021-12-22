#ifndef ImageFilterY_h
#define ImageFilterY_h

#include "itkImageToImageFilter.h"

#include "itkRecursiveGaussianImageFilter.h"

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


  /** Image dimension. */
  static constexpr unsigned int ImageDimension = TImage::ImageDimension;


  /**  Smoothing filter type */
  using InternalGaussianFilterType = RecursiveGaussianImageFilter<TImage, TImage>;

  /**  Pointer to a gaussian filter.  */
  using InternalGaussianFilterPointer = typename InternalGaussianFilterType::Pointer;

protected:
  ImageFilter() = default;
  ~ImageFilter() override = default;

  /** Does the real work. */
  void
  GenerateData() override;
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "ImageFilterY.hxx"
#endif


#endif // ImageFilterY_h
