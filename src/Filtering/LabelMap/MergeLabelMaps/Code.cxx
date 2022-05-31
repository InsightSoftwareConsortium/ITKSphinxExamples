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
#include "itkBinaryImageToShapeLabelMapFilter.h"
#include "itkMergeLabelMapFilter.h"

int
main()
{
  using ImageType = itk::Image<int, 3>;

  // Binary Image to Shape Label Map.
  using BI2SLMType = itk::BinaryImageToShapeLabelMapFilter<ImageType>;
  using LabelMapType = BI2SLMType::OutputImageType;
  using LabelObjectType = BI2SLMType::LabelObjectType;

  using MergerType = itk::MergeLabelMapFilter<LabelMapType>;
  auto merger = MergerType::New();
  merger->SetMethod(itk::MergeLabelMapFilterEnums::ChoiceMethod::PACK);

  int noObjects = 4;

  for (int i = 1; i <= noObjects; ++i)
  {
    auto labelMap = LabelMapType::New();
    auto labelObject = LabelObjectType::New();

    labelObject->SetLabel(1);
    labelMap->AddLabelObject(labelObject);
    labelMap->Update();

    merger->SetInput(i - 1, labelMap);
  }

  merger->Update();
  std::cout << "number of objects:  " << merger->GetOutput()->GetNumberOfLabelObjects() << "\n";
  std::cout << "number of expected objects:  " << noObjects << "\n";

  return EXIT_SUCCESS;
}
