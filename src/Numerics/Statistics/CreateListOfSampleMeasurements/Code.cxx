/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include "itkListSample.h"
#include "itkVector.h"

int
main()
{
  using MeasurementVectorType = itk::Vector<float, 3>;
  using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;
  auto sample = SampleType::New();

  MeasurementVectorType mv;
  mv[0] = 1.0;
  mv[1] = 2.0;
  mv[2] = 4.0;

  sample->PushBack(mv);

  sample->Resize(3);

  mv[0] = 2.0;
  mv[1] = 4.0;
  mv[2] = 5.0;
  sample->SetMeasurementVector(1, mv);

  mv[0] = 3.0;
  mv[1] = 8.0;
  mv[2] = 6.0;
  sample->SetMeasurementVector(2, mv);

  for (unsigned long i = 0; i < sample->Size(); ++i)
  {
    std::cout << "id = " << i << "\t measurement vector = " << sample->GetMeasurementVector(i)
              << "\t frequency = " << sample->GetFrequency(i) << std::endl;
  }

  SampleType::Iterator iter = sample->Begin();

  while (iter != sample->End())
  {
    std::cout << "id = " << iter.GetInstanceIdentifier() << "\t measurement vector = " << iter.GetMeasurementVector()
              << "\t frequency = " << iter.GetFrequency() << std::endl;
    ++iter;
  }

  std::cout << "Size = " << sample->Size() << std::endl;
  std::cout << "Total frequency = " << sample->GetTotalFrequency() << std::endl;

  return EXIT_SUCCESS;
}
