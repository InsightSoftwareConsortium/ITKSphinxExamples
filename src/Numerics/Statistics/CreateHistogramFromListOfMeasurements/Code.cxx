/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#include "itkSampleToHistogramFilter.h"
#include "itkListSample.h"
#include "itkHistogram.h"

using MeasurementVectorType = itk::Vector<unsigned char, 1>;
using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;

using HistogramType = itk::Statistics::Histogram<float, itk::Statistics::DenseFrequencyContainer2>;

void
CreateSample(SampleType::Pointer sample);

int
main()
{
  SampleType::Pointer sample = SampleType::New();
  CreateSample(sample);

  using SampleToHistogramFilterType = itk::Statistics::SampleToHistogramFilter<SampleType, HistogramType>;
  SampleToHistogramFilterType::Pointer sampleToHistogramFilter = SampleToHistogramFilterType::New();
  sampleToHistogramFilter->SetInput(sample);

  SampleToHistogramFilterType::HistogramSizeType histogramSize(1);
  histogramSize.Fill(10);
  sampleToHistogramFilter->SetHistogramSize(histogramSize);

  sampleToHistogramFilter->Update();

  const HistogramType * histogram = sampleToHistogramFilter->GetOutput();
  std::cout << "Histogram vector size: " << histogram->GetMeasurementVectorSize() << std::endl;


  for (unsigned int i = 0; i < histogram->GetSize()[0]; i++)
  {
    std::cout << "Frequency of " << i << " : (" << histogram->GetBinMin(0, i) << " to " << histogram->GetBinMax(0, i)
              << ") = " << histogram->GetFrequency(i) << std::endl;
  }

  std::cout << "Total count " << histogram->GetTotalFrequency() << std::endl;

  return EXIT_SUCCESS;
}

void
CreateSample(SampleType::Pointer sample)
{
  MeasurementVectorType mv;
  mv[0] = 1.0;
  sample->PushBack(mv);

  mv[0] = 1.0;
  sample->PushBack(mv);

  mv[0] = 2.0;
  sample->PushBack(mv);
}
