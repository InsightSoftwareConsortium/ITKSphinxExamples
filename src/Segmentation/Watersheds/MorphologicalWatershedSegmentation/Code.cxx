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
#include <iostream>

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkScalarToRGBPixelFunctor.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkVectorGradientAnisotropicDiffusionImageFilter.h"
#include "itkVectorMagnitudeImageFilter.h"
#include "itkMorphologicalWatershedImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkGradientMagnitudeImageFilter.h"

// Run with:
// ./WatershedImageFilter threshold level
// e.g.
// ./WatershedImageFilter 0.005 .5
// (A rule of thumb is to set the Threshold to be about 1 / 100 of the Level.)

using UnsignedCharImageType = itk::Image<unsigned char, 2>;
using FloatImageType = itk::Image<float, 2>;
using RGBPixelType = itk::RGBPixel<unsigned char>;
using RGBImageType = itk::Image<RGBPixelType, 2>;
using LabeledImageType = itk::Image<unsigned long, 2>;

static void CreateImage(UnsignedCharImageType::Pointer image);
static void PerformSegmentation(FloatImageType::Pointer image, const float threshold, const float level);

int main( int argc, char *argv[] )
{
    // Verify arguments
    if (argc < 3 )
    {
        std::cerr << "Parameters " << std::endl;
        std::cerr << " threshold level" << std::endl;
        return 1;
    }

    // Parse arguments
    std::string strThreshold = argv[1];
    float threshold = 0.0;
    std::stringstream ssThreshold;
    ssThreshold << strThreshold;
    ssThreshold >> threshold;

    std::string strLevel = argv[2];
    float level = 0.0;
    std::stringstream ssLevel;
    ssLevel << strLevel;
    ssLevel >> level;

    // Output arguments
    std::cout << "Running with:" << std::endl
              << "Threshold: " << threshold << std::endl
              << "Level: " << level << std::endl;

    UnsignedCharImageType::Pointer image = UnsignedCharImageType::New();
    CreateImage(image);

    using GradientMagnitudeImageFilterType = itk::GradientMagnitudeImageFilter<
            UnsignedCharImageType, FloatImageType >;
    GradientMagnitudeImageFilterType::Pointer gradientMagnitudeImageFilter = GradientMagnitudeImageFilterType::New();
    gradientMagnitudeImageFilter->SetInput(image);
    gradientMagnitudeImageFilter->Update();

    // Custom parameters
    PerformSegmentation(gradientMagnitudeImageFilter->GetOutput(), threshold, level);

    return EXIT_SUCCESS;
}


void CreateImage(UnsignedCharImageType::Pointer image)
{
    // Create a white image with 3 dark regions of different values

    itk::Index<2> start;
    start.Fill(0);

    itk::Size<2> size;
    size.Fill(200);

    itk::ImageRegion<2> region(start,size);
    image->SetRegions(region);
    image->Allocate();
    image->FillBuffer(255);

    itk::ImageRegionIterator<UnsignedCharImageType> imageIterator(image,region);

    while(!imageIterator.IsAtEnd())
    {
        if(imageIterator.GetIndex()[0] > 20 && imageIterator.GetIndex()[0] < 50 &&
           imageIterator.GetIndex()[1] > 20 && imageIterator.GetIndex()[1] < 50)
            imageIterator.Set(50);

        ++imageIterator;
    }

    imageIterator.GoToBegin();

    while(!imageIterator.IsAtEnd())
    {
        if(imageIterator.GetIndex()[0] > 60 && imageIterator.GetIndex()[0] < 80 &&
           imageIterator.GetIndex()[1] > 60 && imageIterator.GetIndex()[1] < 80)
            imageIterator.Set(100);

        ++imageIterator;
    }

    imageIterator.GoToBegin();

    while(!imageIterator.IsAtEnd())
    {
        if(imageIterator.GetIndex()[0] > 100 && imageIterator.GetIndex()[0] < 130 &&
           imageIterator.GetIndex()[1] > 100 && imageIterator.GetIndex()[1] < 130)
            imageIterator.Set(150);

        ++imageIterator;
    }

    using FileWriterType = itk::ImageFileWriter<UnsignedCharImageType>;
    FileWriterType::Pointer writer = FileWriterType::New();
    writer->SetFileName("input.png");
    writer->SetInput(image);
    writer->Update();
}

void PerformSegmentation(FloatImageType::Pointer image, const float threshold, const float level)
{
    using MorphologicalWatershedFilterType = itk::MorphologicalWatershedImageFilter<FloatImageType, LabeledImageType>;
    MorphologicalWatershedFilterType::Pointer watershedFilter = MorphologicalWatershedFilterType::New();
    watershedFilter->SetLevel(level);
    watershedFilter->SetInput(image);
    watershedFilter->Update();

    using RGBFilterType = itk::ScalarToRGBColormapImageFilter<LabeledImageType, RGBImageType>;
    RGBFilterType::Pointer colormapImageFilter = RGBFilterType::New();
    colormapImageFilter->SetInput(watershedFilter->GetOutput());
    colormapImageFilter->SetColormap( itk::RGBColormapFilterEnumType::Jet );
    colormapImageFilter->Update();

    std::stringstream ss;
    ss << "output_" << threshold << "_" << level << ".png";

    using FileWriterType = itk::ImageFileWriter<RGBImageType>;
    FileWriterType::Pointer writer = FileWriterType::New();
    writer->SetFileName(ss.str());
    writer->SetInput(colormapImageFilter->GetOutput());
    writer->Update();

}

