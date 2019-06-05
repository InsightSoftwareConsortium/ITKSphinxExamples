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
#include "itkApproximateSignedDistanceMapImageFilter.h"

#include "itksys/SystemTools.hxx"
#include <sstream>

#ifdef ENABLE_QUICKVIEW
#include "QuickView.h"
#endif

using UnsignedCharImageType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;

static void CreateImage(UnsignedCharImageType::Pointer image);

int main(int argc, char * argv[])
{
    UnsignedCharImageType::Pointer image = UnsignedCharImageType::New();
    if (argc < 2)
    {
        CreateImage(image);
    }
    else
    {
        using ReaderType = itk::ImageFileReader<UnsignedCharImageType>;
        ReaderType::Pointer reader = ReaderType::New();
        reader->SetFileName(argv[1]);
        reader->Update();
        image = reader->GetOutput();
    }

    using ApproximateSignedDistanceMapImageFilterType = itk::ApproximateSignedDistanceMapImageFilter< UnsignedCharImageType, FloatImageType  >;
    ApproximateSignedDistanceMapImageFilterType::Pointer approximateSignedDistanceMapImageFilter =
            ApproximateSignedDistanceMapImageFilterType::New();
    approximateSignedDistanceMapImageFilter->SetInput(image);
    approximateSignedDistanceMapImageFilter->SetInsideValue(255);
    approximateSignedDistanceMapImageFilter->SetOutsideValue(0);

#ifdef ENABLE_QUICKVIEW
    QuickView viewer;
    viewer.AddImage(
            image.GetPointer(),true,
            argc > 1 ? itksys::SystemTools::GetFilenameName(argv[1]) : "Generated image");

    std::stringstream desc;
    desc << "Approximate Signed Distance";
    viewer.AddImage(
            approximateSignedDistanceMapImageFilter->GetOutput(),
            true,
            desc.str());

    viewer.Visualize();
#endif

    return EXIT_SUCCESS;
}


void CreateImage(UnsignedCharImageType::Pointer image)
{
    // Create an image
    itk::Index<2> start;
    start.Fill(0);

    itk::Size<2> size;
    size.Fill(100);

    itk::ImageRegion<2> region(start, size);
    image->SetRegions(region);
    image->Allocate();
    image->FillBuffer(0);

    // Create a line of white pixels
    for(unsigned int i = 40; i < 60; ++i)
    {
        itk::Index<2> pixel;
        pixel.Fill(i);
        image->SetPixel(pixel, 255);
    }

}
