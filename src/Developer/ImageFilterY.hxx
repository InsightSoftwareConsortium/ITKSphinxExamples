#ifndef __ImageFilterY_hxx
#define __ImageFilterY_hxx

#include "ImageFilterY.h"
#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"

namespace itk
{

template <class TImage>
ImageFilter<TImage>::ImageFilter() = default;

template <class TImage>
void
ImageFilter<TImage>::GenerateData()
{
  InternalGaussianFilterPointer smoothingFilters[ImageDimension];

  // Instantiate all filters
  for (unsigned int i = 0; i < ImageDimension; i++)
  {
    smoothingFilters[i] = InternalGaussianFilterType::New();
    smoothingFilters[i]->SetOrder(GaussianOrderEnum::ZeroOrder);
    smoothingFilters[i]->SetDirection(i);
  }

  // Connect all filters (start at 1 because 0th filter is connected to the input
  for (unsigned int i = 1; i < ImageDimension; i++)
  {
    smoothingFilters[i]->SetInput(smoothingFilters[i - 1]->GetOutput());
  }

  const typename TImage::ConstPointer inputImage(this->GetInput());

  const typename TImage::RegionType region = inputImage->GetRequestedRegion();

  smoothingFilters[0]->SetInput(inputImage);

  smoothingFilters[ImageDimension - 1]->Update();

  // Copy the output from the last filter
  // this->GraftOutput( m_SmoothingFilters[ImageDimension-1]->GetOutput() );
  this->GetOutput()->Graft(smoothingFilters[ImageDimension - 1]->GetOutput());
}

} // namespace itk


#endif
