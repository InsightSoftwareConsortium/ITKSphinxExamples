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
#include "itkMinMaxCurvatureFlowImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#ifdef ENABLE_QUICKVIEW
#include "QuickView.h"
#endif

int main( int argc, char *argv[])
{
    if( argc < 2 )
    {
        std::cerr << "Usage: " << argv[0];
        std::cerr << " inputImage [iterations]" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inputFileName = argv[1];

    int iterations = 5;
    if (argc > 2)
    {
        std::stringstream ss(argv[2]);
        ss >> iterations;
    }
    std::string inputFilename = argv[1];

    using PixelType = float;
    constexpr unsigned int Dimension = 2;

    using ImageType = itk::Image< PixelType, Dimension >;
    using ReaderType = itk::ImageFileReader< ImageType >;
    using MinMaxCurvatureFlowImageFilterType = itk::MinMaxCurvatureFlowImageFilter< ImageType, ImageType >;
    using SubtractType = itk::SubtractImageFilter<ImageType>;

    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName( inputFilename );

    MinMaxCurvatureFlowImageFilterType::Pointer minMaxCurvatureFlowImageFilter = MinMaxCurvatureFlowImageFilterType::New();
    minMaxCurvatureFlowImageFilter->SetInput( reader->GetOutput() );
    minMaxCurvatureFlowImageFilter->SetNumberOfIterations( iterations );
    minMaxCurvatureFlowImageFilter->SetTimeStep( 0.125 );

    SubtractType::Pointer diff = SubtractType::New();
    diff->SetInput1(reader->GetOutput());
    diff->SetInput2(minMaxCurvatureFlowImageFilter->GetOutput());

#ifdef ENABLE_QUICKVIEW
    QuickView viewer;
    viewer.AddImage(
            reader->GetOutput(),true,
            itksys::SystemTools::GetFilenameName(inputFilename));

    std::stringstream desc;
    desc << "MinMaxCurvatureFlow, iterations = " << iterations;
    viewer.AddImage(
            minMaxCurvatureFlowImageFilter->GetOutput(),
            true,
            desc.str());

    std::stringstream desc2;
    desc2 << "Original - Median";
    viewer.AddImage(
            diff->GetOutput(),
            true,
            desc2.str());

    viewer.Visualize();
#endif

    return EXIT_SUCCESS;
}

