#ifndef itkOilPaintingImageFilter_h
#define itkOilPaintingImageFilter_h

#include "itkImageToImageFilter.h"
#include "itkNeighborhoodIterator.h"

namespace itk
{
/** \class OilPaintingImageFilter
 * \brief Implements oil painting artistic image filter.
 *
 * Default number of bins is 20.
 * Default radius is 5, meaning a window of 11x11x11 for 3D images.
 *
 * \ingroup ImageFilters
 */
template <class TImage>
class OilPaintingImageFilter : public ImageToImageFilter<TImage, TImage>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(OilPaintingImageFilter);
  /** Standard class type alias. */
  using Self = OilPaintingImageFilter;
  using Superclass = ImageToImageFilter<TImage, TImage>;
  using Pointer = SmartPointer<Self>;
  using RadiusType = typename NeighborhoodIterator<TImage>::RadiusType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(OilPaintingImageFilter, ImageToImageFilter);

  itkSetMacro(NumberOfBins, unsigned int);
  itkGetConstMacro(NumberOfBins, unsigned int);

  itkSetMacro(Radius, RadiusType);
  itkGetConstMacro(Radius, const RadiusType);
  void
  SetRadius(unsigned int radius);

protected:
  OilPaintingImageFilter();
  ~OilPaintingImageFilter() override = default;

  void
  BeforeThreadedGenerateData() override;

  /** Does the real work. */
  void
  DynamicThreadedGenerateData(const typename TImage::RegionType & outputRegionForThread) override;

private:
  typename TImage::ValueType                        m_Maximum, m_Minimum;
  typename NeighborhoodIterator<TImage>::RadiusType m_Radius;
  unsigned int                                      m_NumberOfBins;
};
} // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkOilPaintingImageFilter.hxx"
#endif

#endif // itkOilPaintingImageFilter_h
