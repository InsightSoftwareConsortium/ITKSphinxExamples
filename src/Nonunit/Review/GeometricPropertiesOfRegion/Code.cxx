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
#include "itkImageRegionIterator.h"
#include "itkImageFileReader.h"
#include "itkLabelGeometryImageFilter.h"
#include "itkLabelToRGBImageFilter.h"

#ifdef ENABLE_QUICKVIEW
#include "QuickView.h"
#endif

#include <sstream>

using ImageType = itk::Image<unsigned int, 2>;
using RGBPixelType = itk::RGBPixel<unsigned char>;
using RGBImageType = itk::Image<RGBPixelType, 2>;

static void CreateIntensityImage(ImageType::Pointer image);
static void CreateLabelImage(ImageType::Pointer image);

int main(int argc, char *argv[])
{
    ImageType::Pointer labelImage = ImageType::New();
    ImageType::Pointer intensityImage = ImageType::New();
    int label = 1;

    if (argc < 2)
    {
        // Create a label image that is 0 in the background and where the
        // objects are labeled
        CreateLabelImage(labelImage);
        labelImage->Print(std::cout);
        // Create an intensity image.  Some LabelGeometry features (such as
        // weighted centroid and integrated intensity) depend on an
        // intensity image.
        CreateIntensityImage(intensityImage);
    }
    else if (argc > 3)
    {
        using ImageReaderType = itk::ImageFileReader< ImageType  >;
        ImageReaderType::Pointer labelReader =
                ImageReaderType::New();
        labelReader->SetFileName(argv[1]);
        labelReader->Update();

        labelImage = labelReader->GetOutput();

        ImageReaderType::Pointer intensityReader =
                ImageReaderType::New();
        intensityReader->SetFileName(argv[2]);
        intensityReader->Update();

        intensityImage = intensityReader->GetOutput();

        label = std::stoi(argv[3]);
    }

    // NOTE: As of April 8, 2015 the filter does not work with non-zero
    // origins
    double origin[2] = {0.0, 0.0};
    labelImage->SetOrigin(origin);
    intensityImage->SetOrigin(origin);

    using LabelGeometryImageFilterType = itk::LabelGeometryImageFilter< ImageType >;
    LabelGeometryImageFilterType::Pointer labelGeometryImageFilter = LabelGeometryImageFilterType::New();
    labelGeometryImageFilter->SetInput( labelImage );
    labelGeometryImageFilter->SetIntensityInput( intensityImage );

    // These generate optional outputs.
    labelGeometryImageFilter->CalculatePixelIndicesOn();
    labelGeometryImageFilter->CalculateOrientedBoundingBoxOn();
    labelGeometryImageFilter->CalculateOrientedLabelRegionsOn();
    labelGeometryImageFilter->CalculateOrientedIntensityRegionsOn();

    labelGeometryImageFilter->Update();
    LabelGeometryImageFilterType::LabelsType allLabels =
            labelGeometryImageFilter->GetLabels();

    using RGBFilterType = itk::LabelToRGBImageFilter<ImageType, RGBImageType>;
    RGBFilterType::Pointer rgbLabelImage =
            RGBFilterType::New();
    rgbLabelImage->SetInput(labelImage);

    using RGBFilterType = itk::LabelToRGBImageFilter<ImageType, RGBImageType>;
    RGBFilterType::Pointer rgbOrientedImage =
            RGBFilterType::New();
    rgbOrientedImage->SetInput(labelGeometryImageFilter->GetOrientedLabelImage(allLabels[label]));

#ifdef ENABLE_QUICKVIEW
    QuickView viewer;
    viewer.ShareCameraOff();
    viewer.InterpolateOff();

    viewer.AddImage(
            rgbLabelImage->GetOutput(),
            true,
            argc > 3 ? itksys::SystemTools::GetFilenameName(argv[1]) : "Generated label image");
    viewer.AddImage(
            intensityImage.GetPointer(),
            true,
            argc > 3 ? itksys::SystemTools::GetFilenameName(argv[2]) : "Generated intensity image");

    std::stringstream desc;
    desc << "Oriented Label: " << allLabels[label];
    viewer.AddImage(
            rgbOrientedImage->GetOutput(),
            true,
            desc.str());

    std::stringstream desc2;
    desc2 << "Oriented Intensity: " << allLabels[label];
    viewer.AddImage(
            labelGeometryImageFilter->GetOrientedIntensityImage(allLabels[label]),
            true,
            desc2.str());
    viewer.Visualize();
#endif

    LabelGeometryImageFilterType::LabelsType::iterator allLabelsIt;
    std::cout << "Number of labels: "
              << labelGeometryImageFilter->GetNumberOfLabels() << std::endl;
    std::cout << std::endl;

    for( allLabelsIt = allLabels.begin(); allLabelsIt != allLabels.end(); allLabelsIt++ )
    {
        LabelGeometryImageFilterType::LabelPixelType labelValue = *allLabelsIt;
        std::cout << "\tLabel: "
                  << (int)labelValue << std::endl;
        std::cout << "\tVolume: "
                  << labelGeometryImageFilter->GetVolume(labelValue) << std::endl;
        std::cout << "\tIntegrated Intensity: "
                  << labelGeometryImageFilter->GetIntegratedIntensity(labelValue) << std::endl;
        std::cout << "\tCentroid: "
                  << labelGeometryImageFilter->GetCentroid(labelValue) << std::endl;
        std::cout << "\tWeighted Centroid: "
                  << labelGeometryImageFilter->GetWeightedCentroid(labelValue) << std::endl;
        std::cout << "\tAxes Length: "
                  << labelGeometryImageFilter->GetAxesLength(labelValue) << std::endl;
        std::cout << "\tMajorAxisLength: "
                  << labelGeometryImageFilter->GetMajorAxisLength(labelValue) << std::endl;
        std::cout << "\tMinorAxisLength: "
                  << labelGeometryImageFilter->GetMinorAxisLength(labelValue) << std::endl;
        std::cout << "\tEccentricity: "
                  << labelGeometryImageFilter->GetEccentricity(labelValue) << std::endl;
        std::cout << "\tElongation: "
                  << labelGeometryImageFilter->GetElongation(labelValue) << std::endl;
        std::cout << "\tOrientation: "
                  << labelGeometryImageFilter->GetOrientation(labelValue) << std::endl;
        std::cout << "\tBounding box: "
                  << labelGeometryImageFilter->GetBoundingBox(labelValue) << std::endl;

        std::cout << std::endl << std::endl;
    }

    return EXIT_SUCCESS;
}

void CreateIntensityImage(ImageType::Pointer image)
{
    // Create a random image.
    ImageType::IndexType start;
    start.Fill(0);

    ImageType::SizeType size;
    size.Fill(20);

    ImageType::RegionType region;
    region.SetSize(size);
    region.SetIndex(start);
    image->SetRegions(region);
    image->Allocate();

    itk::ImageRegionIterator<ImageType> imageIterator(image,image->GetLargestPossibleRegion());
    // Make a random image
    // Create an unchanging seed.
    srand(1);
    while(!imageIterator.IsAtEnd())
    {
        int randomNumber = rand() % 255;
        imageIterator.Set( randomNumber );
        ++imageIterator;
    }
}

void CreateLabelImage(ImageType::Pointer image)
{
    // Create a black image with labeled squares.
    ImageType::IndexType start;
    start.Fill(0);

    ImageType::SizeType size;
    size.Fill(20);

    ImageType::RegionType region;
    region.SetSize(size);
    region.SetIndex(start);
    image->SetRegions(region);
    image->Allocate();

    itk::ImageRegionIterator<ImageType> imageIterator(image,image->GetLargestPossibleRegion());

    // Make a square
    while(!imageIterator.IsAtEnd())
    {
        if((imageIterator.GetIndex()[0] > 5 && imageIterator.GetIndex()[0] < 10) &&
           (imageIterator.GetIndex()[1] > 5 && imageIterator.GetIndex()[1] < 10) )
        {
            imageIterator.Set(85);
        }
        else if((imageIterator.GetIndex()[0] > 11 && imageIterator.GetIndex()[0] < 17) &&
                (imageIterator.GetIndex()[1] > 11 && imageIterator.GetIndex()[1] < 17) )
        {
            imageIterator.Set(127);
        }
        else if((imageIterator.GetIndex()[0] > 11 && imageIterator.GetIndex()[0] < 17) &&
                (imageIterator.GetIndex()[1] > 1 && imageIterator.GetIndex()[1] < 5) )
        {
            imageIterator.Set(191);
        }
        else
        {
            imageIterator.Set(0);
        }

        ++imageIterator;
    }
}
