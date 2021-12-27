#ifndef ImageSource_hxx
#define ImageSource_hxx

#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"

namespace itk
{

template <typename TImage>
void
ImageSource<TImage>::GenerateData()
{
  double a = 2.1;
  itkExceptionMacro("Here is a variable: " << a << " and then more text.");
}

} // namespace itk


#endif
