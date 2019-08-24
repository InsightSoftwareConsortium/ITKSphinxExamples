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
#include "itkLabelContourImageFilter.h"
#include "itkConnectedComponentImageFilter.h"
#include "itkScalarToRGBColormapImageFilter.h"

#include "itksys/SystemTools.hxx"
#include <sstream>

#ifdef ENABLE_QUICKVIEW
#include "QuickView.h"
#endif

namespace
{
    using PixelType = unsigned char;
    using RGBPixelType = itk::RGBPixel<unsigned char>;
    using ImageType = itk::Image<PixelType, 2>;
    using RGBImageType = itk::Image<RGBPixelType, 2>;
}

static void CreateImage(ImageType::Pointer image);

int main(int argc, char *argv[])
{
    // Create or read an image
    ImageType::Pointer image;
    if( argc < 2 )
    {
        image = ImageType::New();
        CreateImage(image.GetPointer());
    }
    else
    {
        using ReaderType = itk::ImageFileReader<ImageType>;
        ReaderType::Pointer reader =
                ReaderType::New();
        reader->SetFileName(argv[1]);
        reader->Update();

        image = reader->GetOutput();
    }

    // Generate connected components
    using ConnectedComponentImageFilterType = itk::ConnectedComponentImageFilter <ImageType, ImageType >;
    ConnectedComponentImageFilterType::Pointer connectedComponentImageFilter
            = ConnectedComponentImageFilterType::New ();
    connectedComponentImageFilter->SetInput(image);

    // Generate contours for each component
    using LabelContourImageFilterType = itk::LabelContourImageFilter<ImageType, ImageType>;
    LabelContourImageFilterType::Pointer labelContourImageFilter =
            LabelContourImageFilterType::New();
    labelContourImageFilter->SetInput(connectedComponentImageFilter->GetOutput());

    using RGBFilterType = itk::ScalarToRGBColormapImageFilter<ImageType, RGBImageType>;
    RGBFilterType::Pointer rgbFilter = RGBFilterType::New();
    rgbFilter->SetInput( labelContourImageFilter->GetOutput() );
    rgbFilter->SetColormap( itk::RGBColormapFilterEnumType::Jet );

#ifdef ENABLE_QUICKVIEW
    QuickView viewer;
    viewer.AddImage(
            image.GetPointer(),true,
            argc > 1 ? itksys::SystemTools::GetFilenameName(argv[1]) : "Generated image");

    std::stringstream desc;
    desc << "LabelContourImageFilter";
    viewer.AddRGBImage(
            rgbFilter->GetOutput(),
            true,
            desc.str());

    viewer.Visualize();
#endif
    return EXIT_SUCCESS;
}

void CreateImage(ImageType::Pointer image)
{
    // Create an image with 2 connected components
    ImageType::RegionType region;
    ImageType::IndexType start;
    start[0] = 0;
    start[1] = 0;

    ImageType::SizeType size;
    unsigned int NumRows = 200;
    unsigned int NumCols = 300;
    size[0] = NumRows;
    size[1] = NumCols;

    region.SetSize(size);
    region.SetIndex(start);

    image->SetRegions(region);
    image->Allocate();

    // Make a square
    for(unsigned int r = 20; r < 80; r++)
    {
        for(unsigned int c = 30; c < 100; c++)
        {
            ImageType::IndexType pixelIndex;
            pixelIndex[0] = r;
            pixelIndex[1] = c;

            image->SetPixel(pixelIndex, 255);
        }
    }

    // Make another square
    for(unsigned int r = 100; r < 130; r++)
    {
        for(unsigned int c = 115; c < 160; c++)
        {
            ImageType::IndexType pixelIndex;
            pixelIndex[0] = r;
            pixelIndex[1] = c;

            image->SetPixel(pixelIndex, 255);
        }
    }
}

