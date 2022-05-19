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

using FloatScalarImageType = itk::Image<float, 2>;

itk::ImageBase<2>::Pointer
CreateImageWithSameType(const itk::ImageBase<2> * input);
void
OutputImageType(const itk::ImageBase<2> * input);

int
main()
{
  FloatScalarImageType::Pointer floatImage = FloatScalarImageType::New();
  itk::ImageBase<2>::Pointer    floatCopy = CreateImageWithSameType(floatImage);
  OutputImageType(floatCopy);

  return EXIT_SUCCESS;
}

itk::ImageBase<2>::Pointer
CreateImageWithSameType(const itk::ImageBase<2> * input)
{
  OutputImageType(input);
  itk::LightObject::Pointer objectCopyLight = input->CreateAnother();

  itk::ImageBase<2>::Pointer objectCopy = dynamic_cast<itk::ImageBase<2> *>(objectCopyLight.GetPointer());
  OutputImageType(objectCopy);
  return objectCopy;
}

void
OutputImageType(const itk::ImageBase<2> * input)
{
  if (dynamic_cast<const FloatScalarImageType *>(input))
  {
    std::cout << "Image type FloatScalarImageType" << std::endl;
  }
  else
  {
    std::cout << "Image is Invalid type!" << std::endl;
  }
}
