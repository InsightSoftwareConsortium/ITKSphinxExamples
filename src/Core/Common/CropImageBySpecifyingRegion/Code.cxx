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
// This is different from CropImageFilter only in the way
// that the region to crop is specified.
#include "itkImage.h"
#include <itkImageFileReader.h>
#include <itkExtractImageFilter.h>

int main(int, char *[])
{
    using ImageType = itk::Image<unsigned char, 2>;

    ImageType::IndexType start;
    start.Fill(0);

    ImageType::SizeType size;
    size.Fill(10);

    ImageType::RegionType region(start, size);

    ImageType::Pointer image = ImageType::New();
    image->SetRegions(region);
    image->Allocate();
    image->FillBuffer(5);

    std::cout << "Image largest region: " << image->GetLargestPossibleRegion() << std::endl;

    ImageType::IndexType desiredStart;
    desiredStart.Fill(3);

    ImageType::SizeType desiredSize;
    desiredSize.Fill(4);

    ImageType::RegionType desiredRegion(desiredStart, desiredSize);

    std::cout << "desiredRegion: " << desiredRegion << std::endl;

    using FilterType = itk::ExtractImageFilter< ImageType, ImageType >;
    FilterType::Pointer filter = FilterType::New();
    filter->SetExtractionRegion(desiredRegion);
    filter->SetInput(image);
#if ITK_VERSION_MAJOR >= 4
    filter->SetDirectionCollapseToIdentity(); // This is required.
#endif
    filter->Update();

    ImageType::Pointer output = filter->GetOutput();
    output->DisconnectPipeline();
    output->FillBuffer(2);

    itk::Index<2> index;
    index.Fill(5);

    std::cout << "new largest region: " << output->GetLargestPossibleRegion() << std::endl;
    std::cout << "new: " << (int)output->GetPixel(index) << std::endl;
    std::cout << "Original: " << (int)image->GetPixel(index) << std::endl;

    return EXIT_SUCCESS;
}

