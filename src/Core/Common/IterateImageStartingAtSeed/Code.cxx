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
#include "itkImageFileWriter.h"
#include "itkFloodFilledImageFunctionConditionalIterator.h"
#include "itkBinaryThresholdImageFunction.h"
#include "itkImageFileWriter.h"

using ImageType = itk::Image< unsigned char, 2 >;

static void CreateImage(ImageType::Pointer image);

int main( int argc, char *argv[])
{
    ImageType::Pointer image = ImageType::New();
    CreateImage(image);

    using FunctionType = itk::BinaryThresholdImageFunction< ImageType, double >;
    FunctionType::Pointer function = FunctionType::New();
    function->SetInputImage(image);
    function->ThresholdAbove(100); // we are looking to capture 255

    using IteratorType = itk::FloodFilledImageFunctionConditionalIterator< ImageType, FunctionType >;

    itk::Index<2> seed;
    seed[0] = 25;
    seed[1] = 25;

    std::vector<itk::Index<2> > seeds;
    seeds.push_back(seed);

    IteratorType it (image, function, seeds);
    it.GoToBegin();

    while ( !it.IsAtEnd() )
    {
        std::cout << it.GetIndex() << std::endl;
        ++it;
    }

    return EXIT_SUCCESS;
}

void CreateImage(ImageType::Pointer image)
{
    itk::Index<2> start;
    start.Fill(0);

    itk::Size<2> size;
    size.Fill(100);

    itk::ImageRegion<2> region(start,size);
    image->SetRegions(region);
    image->Allocate();
    image->FillBuffer(0);

    // The line doesn't work at the moment, because it needs 8-connectivity.

    // Make a line
    for(unsigned int i = 20; i < 50; ++i)
    {
        itk::Index<2> pixelIndex;
        pixelIndex.Fill(i);

        image->SetPixel(pixelIndex, 255);
    }

    // Make a square
//   for(unsigned int r = 20; r < 50; r++)
//     {
//     for(unsigned int c = 20; c < 50; c++)
//       {
//       itk::Index<2> pixelIndex;
//       pixelIndex[0] = r;
//       pixelIndex[1] = c;
//
//       image->SetPixel(pixelIndex, 255);
//       }
//     }
}

