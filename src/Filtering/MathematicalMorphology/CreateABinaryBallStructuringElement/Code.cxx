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

#include "itkBinaryBallStructuringElement.h"

int
main(int, char *[])
{
  constexpr unsigned int Dimension = 3;
  using PixelType = float;

  using StructuringElementType = itk::BinaryBallStructuringElement<PixelType, Dimension>;
  StructuringElementType structuringElement;
  structuringElement.SetRadius(5);
  structuringElement.CreateStructuringElement();

  return EXIT_SUCCESS;
}
