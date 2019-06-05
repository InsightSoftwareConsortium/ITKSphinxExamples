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
#include "itkCastImageFilter.h"
#include "itkImageFileReader.h"
#include "itkVectorGradientAnisotropicDiffusionImageFilter.h"
#include "itkVectorToRGBImageAdaptor.h"
#include "itkRGBToVectorImageAdaptor.h"
#include "itkCastImageFilter.h"

#include "itksys/SystemTools.hxx"
#include <sstream>

#include "QuickView.h"

int main( int argc, char *argv[])
{
    // Verify arguments
    if( argc < 2 )
    {
        std::cerr << "Usage: "<< std::endl;
        std::cerr << argv[0];
        std::cerr << " InputFileName";
        std::cerr << " [NumberOfIterations] ";
        std::cerr << " [Conductance]" << std::endl;
        return EXIT_FAILURE;
    }

    // 0) Parse arguments
    std::string inputFileName = argv[1];

    using FloatImageType = itk::Image< itk::Vector<float, 3>, 2 >;
    using RGBImageType = itk::Image< itk::RGBPixel<float>, 2 >;

    // 1) Read the RGB image
    using ReaderType = itk::ImageFileReader< RGBImageType >;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( inputFileName );

    // 2) Cast to Vector image for processing
    using AdaptorInputType = itk::RGBToVectorImageAdaptor<RGBImageType>;
    AdaptorInputType::Pointer adaptInput = AdaptorInputType::New();
    adaptInput->SetImage(reader->GetOutput());
    using CastInputType = itk::CastImageFilter<AdaptorInputType,FloatImageType>;
    CastInputType::Pointer castInput = CastInputType::New();
    castInput->SetInput(adaptInput);

    // 3) Smooth the image
    using VectorGradientAnisotropicDiffusionImageFilterType = itk::VectorGradientAnisotropicDiffusionImageFilter< FloatImageType,
            FloatImageType >;
    VectorGradientAnisotropicDiffusionImageFilterType::Pointer filter =
            VectorGradientAnisotropicDiffusionImageFilterType::New();
    filter->SetInput( castInput->GetOutput() );
    filter->SetTimeStep(0.125);
    if (argc > 2)
    {
        filter->SetNumberOfIterations(atoi(argv[2]));
    }
    if (argc > 3)
    {
        filter->SetConductanceParameter(atof(argv[3]));
    }

    // 4) Cast the Vector image to an RGB image for display
    using AdaptorOutputType = itk::VectorToRGBImageAdaptor<FloatImageType>;
    AdaptorOutputType::Pointer adaptOutput = AdaptorOutputType::New();
    adaptOutput->SetImage(filter->GetOutput());
    using CastOutputType = itk::CastImageFilter<AdaptorOutputType,RGBImageType>;
    CastOutputType::Pointer castOutput = CastOutputType::New();
    castOutput->SetInput(adaptOutput);

    // 5) Display the input and smoothed images
    QuickView viewer;
    viewer.AddRGBImage(
            reader->GetOutput(),
            true,
            itksys::SystemTools::GetFilenameName(inputFileName));

    std::stringstream desc;
    desc << "VectorGradientAnisotropicDiffusionImageFilter\niterations: "
         << filter->GetNumberOfIterations() << " conductance: "
         << filter->GetConductanceParameter();
    viewer.AddRGBImage(
            castOutput->GetOutput(),
            true,
            desc.str());

    viewer.Visualize();

    return EXIT_SUCCESS;
}

