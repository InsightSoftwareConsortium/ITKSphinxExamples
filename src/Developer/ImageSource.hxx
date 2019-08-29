#ifndef __itkImageSource_hxx
#define __itkImageSource_hxx

#include "ImageSource.h"
#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"

namespace itk
{

template <class TImage>
void
ImageFilter<TImage>::GenerateData()
{
  double a = 2.1;
  itkExceptionMacro("Here is a variable: " << a << " and then more text.");
}

} // namespace itk


#endif
