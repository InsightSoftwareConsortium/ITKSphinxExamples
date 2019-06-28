#ifndef __itkMyInPlaceImageFilter_h
#define __itkMyInPlaceImageFilter_h

#include "itkInPlaceImageFilter.h"

namespace itk
{
template< class TImage>
class MyInPlaceImageFilter : public InPlaceImageFilter<TImage>
{
public:
  /** Standard class type alias. */
  using Self = MyInPlaceImageFilter;
  using Superclass = InPlaceImageFilter<TImage>;
  using Pointer = SmartPointer< Self >;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MyInPlaceImageFilter, InPlaceImageFilter);

protected:
  MyInPlaceImageFilter()= default;
  ~MyInPlaceImageFilter() override= default;

  /** Does the real work. */
  void GenerateData() override;

private:
  MyInPlaceImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented

};
} //namespace ITK


#ifndef ITK_MANUAL_INSTANTIATION
#include "MyInPlaceImageFilter.hxx"
#endif


#endif
