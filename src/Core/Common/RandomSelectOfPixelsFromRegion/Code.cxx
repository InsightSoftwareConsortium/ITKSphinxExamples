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
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageRandomConstIteratorWithIndex.h"

int main(int, char *[])
{
    using ImageType = itk::Image<unsigned char, 2>;
    ImageType::Pointer image = ImageType::New();

    ImageType::SizeType regionSize;
    regionSize[0] = 5;
    regionSize[1] = 4;

    ImageType::IndexType regionIndex;
    regionIndex[0] = 0;
    regionIndex[1] = 0;

    ImageType::RegionType region;
    region.SetSize(regionSize);
    region.SetIndex(regionIndex);

    image->SetRegions(region);
    image->Allocate();
    image->FillBuffer(0);

    itk::ImageRandomConstIteratorWithIndex<ImageType> imageIterator(image, image->GetLargestPossibleRegion());
    imageIterator.SetNumberOfSamples(200);
    imageIterator.GoToBegin();

    while(!imageIterator.IsAtEnd())
    {
        std::cout << imageIterator.GetIndex() << std::endl;

        ++imageIterator;
    }

    return EXIT_SUCCESS;
}
