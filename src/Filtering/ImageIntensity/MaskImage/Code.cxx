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
#include "itkConfigure.h"

#if ( ITK_VERSION_MAJOR < 4  ) //These are all defaults in ITKv4
//  Not supported in ITKv3.
int main(int argc, char *argv[])
{
  return 0;
}
#else
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkMaskImageFilter.h"
#include "itkImageRegionIterator.h"
#ifdef ENABLE_QUICKVIEW
#include "QuickView.h"
#endif

using ImageType = itk::Image<unsigned char, 2>;

void CreateHalfMask(ImageType::Pointer image, ImageType::Pointer &mask);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
        return EXIT_FAILURE;
    }

    using ReaderType = itk::ImageFileReader<ImageType>;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    ImageType::Pointer mask = ImageType::New();
    CreateHalfMask(reader->GetOutput(), mask);

    using MaskFilterType = itk::MaskImageFilter< ImageType, ImageType >;
    MaskFilterType::Pointer maskFilter = MaskFilterType::New();
    maskFilter->SetInput(reader->GetOutput());
    maskFilter->SetMaskImage(mask);
    mask->Print(std::cout);
#ifdef ENABLE_QUICKVIEW
    QuickView viewer;
    viewer.AddImage(
            reader->GetOutput(),true,
            itksys::SystemTools::GetFilenameName(argv[1]));

    std::stringstream desc;
    desc << "Mask";
    viewer.AddImage(
            mask.GetPointer(),
            true,
            desc.str());

    std::stringstream desc2;
    desc2 << "MaskFilter";
    viewer.AddImage(
            maskFilter->GetOutput(),
            true,
            desc2.str());

    viewer.Visualize();
#endif
    return EXIT_SUCCESS;
}


void CreateHalfMask(ImageType::Pointer image, ImageType::Pointer &mask)
{
    ImageType::RegionType region = image->GetLargestPossibleRegion();

    mask->SetRegions(region);
    mask->Allocate();

    ImageType::SizeType regionSize = region.GetSize();

    itk::ImageRegionIterator<ImageType> imageIterator(mask,region);

    // Make the left half of the mask white and the right half black
    while(!imageIterator.IsAtEnd())
    {
        if(imageIterator.GetIndex()[0] > static_cast<ImageType::IndexValueType>(regionSize[0]) / 2)
        {
            imageIterator.Set(0);
        }
        else
        {
            imageIterator.Set(255);
        }

        ++imageIterator;
    }

}
#endif

