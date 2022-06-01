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
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "ImageFilterMultipleOutputsDifferentType.h"

int
main()
{
  // Setup types
  using InputImageType = itk::Image<unsigned char, 2>;
  using OutputImageType1 = itk::Image<float, 2>;
  using OutputImageType2 = itk::Image<int, 2>;
  using FilterType = itk::ImageFilterMultipleOutputsDifferentType<InputImageType, OutputImageType1, OutputImageType2>;

  // Create and the filter
  auto filter = FilterType::New();
  filter->Update();

  itk::WriteImage(filter->GetOutput1(), "TestOutput1.jpg");

  itk::WriteImage(filter->GetOutput2(), "TestOutput2.jpg");

  return EXIT_SUCCESS;
}
