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
#include "itkImageFileReader.h"
#include "itkZeroCrossingImageFilter.h"

#include "itksys/SystemTools.hxx"
#include <sstream>

#include "QuickView.h"

using ImageType = itk::Image<float, 2>;

static void CreateImage(ImageType::Pointer image);

int main(int argc, char *argv[])
{
    ImageType::Pointer image = ImageType::New();
    if (argc < 2)
    {
        CreateImage(image);
    }
    else
    {
        using ReaderType = itk::ImageFileReader<ImageType>;
        ReaderType::Pointer reader = ReaderType::New();
        reader->SetFileName(argv[1]);
        reader->Update();
        image = reader->GetOutput();
    }

    using FilterType = itk::ZeroCrossingImageFilter< ImageType, ImageType >;
    FilterType::Pointer filter = FilterType::New();
    filter->SetInput(image);
    filter->SetBackgroundValue(0);
    filter->SetForegroundValue(255);

    QuickView viewer;
    viewer.AddImage(
            image.GetPointer(),true,
            argc > 1 ? itksys::SystemTools::GetFilenameName(argv[1]) : "Generated image");

    std::stringstream desc;
    desc << "Zero Crossing";
    viewer.AddImage(
            filter->GetOutput(),
            true,
            desc.str());

    viewer.Visualize();

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
    image->FillBuffer(-1);

    // Make half of the image negative
    for(unsigned int i = 0; i < 100; ++i)
    {
        for(unsigned int j = 0; j < 50; ++j)
        {
            itk::Index<2> index;
            index[0] = i;
            index[1] = j;
            image->SetPixel(index, 1);
        }
    }
}

