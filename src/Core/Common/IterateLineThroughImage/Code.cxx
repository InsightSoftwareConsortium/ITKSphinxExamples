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
#include "itkRGBPixel.h"
#include "itkImageFileReader.h"
#include "itkImageRegionIterator.h"
#include "itkLineIterator.h"

#include "itksys/SystemTools.hxx"

#ifdef ENABLE_QUICKVIEW
#include "QuickView.h"
#endif

using PixelType = itk::RGBPixel<unsigned char>;
using ImageType = itk::Image<PixelType, 2>;

static void CreateImage(ImageType::Pointer image);

int main(int argc, char*argv[])
{
    ImageType::Pointer image = ImageType::New();
    std::string inputFilename;
    if (argc < 2)
    {
        CreateImage(image);
        inputFilename = "Synthetic";
    }
    else
    {
        using ReaderType = itk::ImageFileReader<ImageType>;
        ReaderType::Pointer reader = ReaderType::New();
        reader->SetFileName (argv[1]);
        reader->Update();
        image = reader->GetOutput();
        inputFilename = argv[1];
    }

    PixelType pixel;
    pixel.SetRed(255);
    pixel.SetGreen(127);
    pixel.SetBlue(50);

    ImageType::RegionType region = image->GetLargestPossibleRegion();
    ImageType::IndexType corner1 = region.GetIndex();
    ImageType::IndexType corner2;

    corner2[0] = corner1[0] + region.GetSize()[0] - 1;
    corner2[1] = corner1[1] + region.GetSize()[1] - 1;

    itk::LineIterator<ImageType> it1(image, corner1, corner2);
    it1.GoToBegin();
    while (!it1.IsAtEnd())
    {

        it1.Set(pixel);
        ++it1;
    }

#ifdef ENABLE_QUICKVIEW
    QuickView viewer;
    if (argc > 1)
    {
        viewer.AddImage<ImageType>(
                image,
                true,
                itksys::SystemTools::GetFilenameName(argv[1]));
    }
    else
    {
        viewer.AddImage<ImageType>(
                image,
                true,
                "Synthetic");
    }
    viewer.Visualize();
#endif
    return EXIT_SUCCESS;
}

void CreateImage(ImageType::Pointer image)
{
    ImageType::SizeType regionSize;
    regionSize.Fill(100);

    ImageType::IndexType regionIndex;
    regionIndex.Fill(0);

    ImageType::RegionType region;
    region.SetSize(regionSize);
    region.SetIndex(regionIndex);

    PixelType pixel;
    pixel.SetRed(0);
    pixel.SetGreen(127);
    pixel.SetBlue(200);

    image->SetRegions(region);
    image->Allocate();
    image->FillBuffer(pixel);

}
