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

#include "itkImage.h"
#include "itkImageDuplicator.h"
#include "itkRandomImageSource.h"

int
main()
{
  constexpr unsigned int Dimension = 2;
  using PixelType = unsigned char;

  using ImageType = itk::Image<PixelType, Dimension>;

  using RandomSourceType = itk::RandomImageSource<ImageType>;

  RandomSourceType::Pointer randomImageSource = RandomSourceType::New();
  randomImageSource->SetNumberOfWorkUnits(1); // to produce non-random results

  ImageType::Pointer image = randomImageSource->GetOutput();

  using DuplicatorType = itk::ImageDuplicator<ImageType>;
  DuplicatorType::Pointer duplicator = DuplicatorType::New();
  duplicator->SetInputImage(image);
  duplicator->Update();

  ImageType::Pointer clonedImage = duplicator->GetOutput();

  return EXIT_SUCCESS;
}
