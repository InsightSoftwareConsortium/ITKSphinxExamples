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
#include "itkContourMeanDistanceImageFilter.h"

#ifdef ENABLE_QUICKVIEW
#include "QuickView.h"
#endif

template<typename TImage>
static void CreateImage1(TImage* const);

template<typename TImage>
static void CreateImage2(TImage* const);

int main(int, char*[])
{
    using ImageType = itk::Image<unsigned char, 2>;

    ImageType::Pointer image1 = ImageType::New();
    CreateImage1(image1.GetPointer());

    ImageType::Pointer image2 = ImageType::New();
    CreateImage2(image2.GetPointer());

    using ContourMeanDistanceImageFilterType = itk::ContourMeanDistanceImageFilter <ImageType, ImageType >;

    ContourMeanDistanceImageFilterType::Pointer contourMeanDistanceImageFilter =
            ContourMeanDistanceImageFilterType::New();
    contourMeanDistanceImageFilter->SetInput1(image1);
    contourMeanDistanceImageFilter->SetInput2(image2);
    contourMeanDistanceImageFilter->Update();

    std::cout << "Mean distance: " << contourMeanDistanceImageFilter->GetMeanDistance() << std::endl;

#ifdef ENABLE_QUICKVIEW
    QuickView viewer;
    viewer.AddImage(image1.GetPointer());
    viewer.AddImage(image2.GetPointer());
    viewer.Visualize();
#endif
    return EXIT_SUCCESS;
}

template<typename TImage>
void CreateImage1(TImage* const image)
{
    // Create an image bigger than the input image and that has dimensions which are powers of two
    typename TImage::IndexType start = {{0,0}};

    typename TImage::SizeType size = {{20,20}};

    itk::ImageRegion<2> region(start, size);

    image->SetRegions(region);
    image->Allocate();
    image->FillBuffer(0);

    // Create a diagonal white line through the image
    for(typename TImage::IndexValueType i = 0; i < 20; i++)
    {
        for(typename TImage::IndexValueType j = 0; j < 20; j++)
        {
            if(i == j)
            {
                itk::Index<2> pixel = {{i,j}};
                image->SetPixel(pixel, 255);
            }
        }
    }
}

template<typename TImage>
void CreateImage2(TImage* const image)
{
    typename TImage::IndexType start = {{0,0}};

    typename TImage::SizeType size = {{20,20}};

    itk::ImageRegion<2> region(start, size);

    image->SetRegions(region);
    image->Allocate();
    image->FillBuffer(0);

    // Create a vertical line of white pixels down the center of the image
    for(typename TImage::IndexValueType i = 0; i < 20; i++)
    {
        for(typename TImage::IndexValueType j = 0; j < 20; j++)
        {
            if(i == 10)
            {
                itk::Index<2> pixel = {{i,j}};
                image->SetPixel(pixel, 255);
            }
        }
    }
}

