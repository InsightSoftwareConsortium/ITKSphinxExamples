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
#include "itkJetColormapFunction.h"
#include "itkRGBPixel.h"

int
main()
{
  using PixelType = itk::RGBPixel<unsigned char>;
  using ColormapType = itk::Function::JetColormapFunction<float, PixelType>;
  ColormapType::Pointer colormap = ColormapType::New();

  colormap->SetMinimumInputValue(0.0);
  colormap->SetMaximumInputValue(1.0);
  std::cout << "0: " << colormap->  operator()(0.0f) << std::endl;
  std::cout << "0.5: " << colormap->operator()(0.5f) << std::endl;
  std::cout << "1: " << colormap->  operator()(1.0f) << std::endl;
  return EXIT_SUCCESS;
}
