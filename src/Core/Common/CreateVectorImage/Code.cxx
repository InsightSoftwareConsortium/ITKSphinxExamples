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
#include "itkVectorImage.h"

int main(int, char *[])
{
    // Create an image
    using ImageType = itk::VectorImage<float, 2>;

    ImageType::IndexType start;
    start.Fill(0);

    ImageType::SizeType size;
    size.Fill(2);

    ImageType::RegionType region(start,size);

    ImageType::Pointer image = ImageType::New();
    image->SetRegions(region);
    image->SetVectorLength(2);
    image->Allocate();

    ImageType::IndexType pixelIndex;
    pixelIndex[0] = 1;
    pixelIndex[1] = 1;

    ImageType::PixelType pixelValue = image->GetPixel(pixelIndex);

    std::cout << "pixel (1,1) = " << pixelValue << std::endl;

    using VariableVectorType = itk::VariableLengthVector<double>;
    VariableVectorType variableLengthVector;
    variableLengthVector.SetSize(2);
    variableLengthVector[0] = 1.1;
    variableLengthVector[1] = 2.2;

    image->SetPixel(pixelIndex, variableLengthVector);

    std::cout << "pixel (1,1) = " << pixelValue << std::endl;

    return EXIT_SUCCESS;
}

