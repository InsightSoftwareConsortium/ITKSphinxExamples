#ifndef __itkOilPaintingImageFilter_hxx
#define __itkOilPaintingImageFilter_hxx

#include "itkOilPaintingImageFilter.h"
#include "itkObjectFactory.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkNeighborhoodIterator.h"
#include "itkMinimumMaximumImageCalculator.h"

namespace itk
{
template<class TImage>
OilPaintingImageFilter<TImage>::OilPaintingImageFilter()
{
    this->m_NumberOfBins=20;
    this->SetRadius(5);
    this->SetDynamicMultiThreading(false);
}

template<class TImage>
void OilPaintingImageFilter<TImage>::SetRadius(unsigned int radius)
{
    for (unsigned int i = 0; i < TImage::ImageDimension; ++i)
      {
      m_Radius[i] = radius;
      }
}

template<class TImage>
void OilPaintingImageFilter<TImage>::BeforeThreadedGenerateData()
{
    using CalculatorType = itk::MinimumMaximumImageCalculator< TImage >;
    typename CalculatorType::Pointer calculatorI = CalculatorType::New();
    calculatorI->SetImage( this->GetInput() );
    calculatorI->Compute();
    m_Maximum = calculatorI->GetMaximum();
    m_Minimum = calculatorI->GetMinimum();
}

template<class TImage>
void OilPaintingImageFilter<TImage>
::ThreadedGenerateData(const typename TImage::RegionType& outputRegionForThread, ThreadIdType /*threadId*/)
{
  typename TImage::ConstPointer input = this->GetInput();
  typename TImage::Pointer output = this->GetOutput();

  itk::ImageRegionIterator<TImage> out(output, outputRegionForThread);
  itk::ConstNeighborhoodIterator<TImage> it(m_Radius, input, outputRegionForThread);

  unsigned long long *bins=new unsigned long long[m_NumberOfBins];

  while(!out.IsAtEnd())
  {
    for (unsigned int i=0; i<m_NumberOfBins; i++)
      {
      bins[i]=0; //reset histogram
      }

    //create histogram of values within the radius
    for (unsigned int i = 0; i < it.Size(); ++i)
      {
      typename TImage::ValueType val=it.GetPixel(i);
      bins[int((m_NumberOfBins-0.001)*(val-m_Minimum)/(m_Maximum-m_Minimum))]++;
      //casting to int rounds towards zero
      //without -0.001, when val=max then we would go over the upper bound (index m_NumberOfBins)
      }

    //find the peak
    unsigned maxIndex=0;
    unsigned long long maxBin=bins[0];
    for (unsigned int i=1; i<m_NumberOfBins; i++)
      {
      if (bins[i]>maxBin)
        {
        maxBin=bins[i];
        maxIndex=i;
        }
      }

    //set middle value of a bin's range as intensity
    out.Set((maxIndex+0.5)*(m_Maximum-m_Minimum)/m_NumberOfBins);

    ++it;
    ++out;
  }

  delete [] bins; //dealloc array
}

}// end namespace

#endif //__itkOilPaintingImageFilter_hxx
