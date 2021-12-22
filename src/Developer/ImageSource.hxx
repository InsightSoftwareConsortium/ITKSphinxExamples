#ifndef __ImageSource_hxx
#define __ImageSource_hxx

#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"

namespace itk
{

template <class TImage>
void
ImageSource<TImage>::GenerateData()
{
  double a = 2.1;
  itkExceptionMacro("Here is a variable: " << a << " and then more text.");
}

} // namespace itk


#endif
