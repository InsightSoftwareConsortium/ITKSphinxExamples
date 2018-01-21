/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkHistogram.h"
#include "itkDenseFrequencyContainer2.h"

int main()
{
  typedef float                                         MeasurementType;
  typedef itk::Statistics::DenseFrequencyContainer2     FrequencyContainerType;

  const unsigned int numberOfComponents = 2;
  typedef itk::Statistics::Histogram< MeasurementType,
    FrequencyContainerType > HistogramType;

  HistogramType::Pointer histogram = HistogramType::New();
  histogram->SetMeasurementVectorSize( numberOfComponents );

  // We initialize it as a 3x3 histogram with equal size intervals.

  HistogramType::SizeType size( numberOfComponents );
  size.Fill(3);
  HistogramType::MeasurementVectorType lowerBound( numberOfComponents );
  HistogramType::MeasurementVectorType upperBound( numberOfComponents );
  lowerBound[0] = 1.1;
  lowerBound[1] = 2.6;
  upperBound[0] = 7.1;
  upperBound[1] = 8.6;

  histogram->Initialize(size, lowerBound, upperBound );

  // Now the histogram is ready for storing frequency values. There
  // are three ways of accessing data elements in the histogram:
  // - using instance identifiers---just like any other Sample object;
  // - using n-dimensional indices---just like an Image object;
  // - using an iterator---just like any other Sample object.
  //
  // In this example, the index (0, 0) refers the same bin as the instance
  // identifier (0) refers to. The instance identifier of the index (0,
  // 1) is (3), (0, 2) is (6), (2, 2) is (8), and so on.

  histogram->SetFrequency(0, 0);
  histogram->SetFrequency(1, 2);
  histogram->SetFrequency(2, 3);
  histogram->SetFrequency(3, 2);
  histogram->SetFrequency(4, 1);
  histogram->SetFrequency(5, 1);
  histogram->SetFrequency(6, 5);
  histogram->SetFrequency(7, 4);
  histogram->SetFrequency(8, 0);

  // Let us examine if the frequency is set correctly by calling the
  // GetFrequency(index) method. We can use the
  // GetFrequency(instance identifier) method for the same purpose.

  HistogramType::IndexType index( numberOfComponents );
  index[0] = 0;
  index[1] = 2;
  std::cout << "Frequency of the bin at index " << index
            << " is " << histogram->GetFrequency(index)
            << " and the bin's instance identifier is "
            << histogram->GetInstanceIdentifier(index) << std::endl;

  return EXIT_SUCCESS;
}
