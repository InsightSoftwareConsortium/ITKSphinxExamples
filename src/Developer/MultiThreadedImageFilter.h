#ifndef __itkImageFilter_h
#define __itkImageFilter_h

#include "itkImageToImageFilter.h"

namespace itk
{
template< class TImage>
class MultiThreadedImageFilter : public ImageToImageFilter< TImage, TImage >
{
public:
  /** Standard class type alias. */
  using Self = MultiThreadedImageFilter;
  using Superclass = ImageToImageFilter< TImage, TImage >;
  using Pointer = SmartPointer< Self >;

  using OutputImageRegionType = typename Superclass::OutputImageRegionType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImageFilter, ImageToImageFilter);

protected:
  MultiThreadedImageFilter(){}
  ~MultiThreadedImageFilter(){}

  virtual void ThreadedGenerateData(const OutputImageRegionType &,
                                    ThreadIdType);

private:
  MultiThreadedImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented

};
} //namespace ITK


#ifndef ITK_MANUAL_INSTANTIATION
#include "MultiThreadedImageFilter.hxx"
#endif


#endif // __itkMultiThreadedImageFilter_h
