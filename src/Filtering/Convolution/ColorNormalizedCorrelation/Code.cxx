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
#include "itkNormalizedCorrelationImageFilter.h"
#include "itkRegionOfInterestImageFilter.h"
#include "itkImageKernelOperator.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkImageFileWriter.h"
#include "itkMinimumMaximumImageCalculator.h"
#include "itkCovariantVector.h"

#ifdef ENABLE_QUICKVIEW
#include "QuickView.h"
#endif

#include <iostream>
#include <string>

// Vector types
using FloatVectorType = itk::CovariantVector<float, 3>;
using UnsignedCharVectorType = itk::CovariantVector<unsigned char, 3>;

// Vector image types
using FloatVectorImageType = itk::Image<FloatVectorType, 2>;
using UnsignedCharVectorImageType = itk::Image<UnsignedCharVectorType, 2>;

// Scalar image types
using FloatImageType = itk::Image<float, 2>;
using UnsignedCharImageType = itk::Image<unsigned char, 2>;

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cerr << "Required: filename" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];

    using ReaderType = itk::ImageFileReader<FloatVectorImageType>;

    // Read the image
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(filename.c_str());
    reader->Update();

    // Extract a small region
    using ExtractFilterType = itk::RegionOfInterestImageFilter< FloatVectorImageType,
            FloatVectorImageType >;

    ExtractFilterType::Pointer extractFilter = ExtractFilterType::New();

    FloatImageType::IndexType start;
    start.Fill(50);

    FloatImageType::SizeType patchSize;
    patchSize.Fill(51);

    FloatImageType::RegionType desiredRegion(start,patchSize);

    extractFilter->SetRegionOfInterest(desiredRegion);
    extractFilter->SetInput(reader->GetOutput());
    extractFilter->Update();

    // Perform normalized correlation
    // <input type, mask type (not used), output type>
    using CorrelationFilterType = itk::NormalizedCorrelationImageFilter<FloatVectorImageType, FloatVectorImageType, FloatImageType>;

    itk::ImageKernelOperator<FloatVectorType> kernelOperator;
    kernelOperator.SetImageKernel(extractFilter->GetOutput());

    // The radius of the kernel must be the radius of the patch, NOT the size of the patch
    itk::Size<2> radius = extractFilter->GetOutput()->GetLargestPossibleRegion().GetSize();
    radius[0] = (radius[0]-1) / 2;
    radius[1] = (radius[1]-1) / 2;

    kernelOperator.CreateToRadius(radius);

    CorrelationFilterType::Pointer correlationFilter = CorrelationFilterType::New();
    correlationFilter->SetInput(reader->GetOutput());
    correlationFilter->SetTemplate(kernelOperator);
    correlationFilter->Update();

    using MinimumMaximumImageCalculatorType = itk::MinimumMaximumImageCalculator <FloatImageType>;

    MinimumMaximumImageCalculatorType::Pointer minimumMaximumImageCalculatorFilter
            = MinimumMaximumImageCalculatorType::New ();
    minimumMaximumImageCalculatorFilter->SetImage(correlationFilter->GetOutput());
    minimumMaximumImageCalculatorFilter->Compute();

    itk::Index<2> maximumCorrelationPatchCenter = minimumMaximumImageCalculatorFilter->GetIndexOfMaximum();
    std::cout << "Maximum: " << maximumCorrelationPatchCenter << std::endl;

    // Note that the best correlation is at the center of the patch we extracted (ie. (75, 75) rather than the corner (50,50)

    using RescaleFilterType = itk::RescaleIntensityImageFilter< FloatImageType, UnsignedCharImageType >;
    using WriterType = itk::ImageFileWriter<UnsignedCharVectorImageType>;
    {
        RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
        rescaleFilter->SetInput(correlationFilter->GetOutput());
        rescaleFilter->SetOutputMinimum(0);
        rescaleFilter->SetOutputMaximum(255);
        rescaleFilter->Update();

        WriterType::Pointer writer = WriterType::New();
        writer->SetInput(rescaleFilter->GetOutput());
        writer->SetFileName("correlation.png");
        writer->Update();
    }

    {
        RescaleFilterType::Pointer rescaleFilter = RescaleVectorFilterType::New();
        rescaleFilter->SetInput(extractFilter->GetOutput());
        rescaleFilter->SetOutputMinimum(0);
        rescaleFilter->SetOutputMaximum(255);
        rescaleFilter->Update();

        WriterType::Pointer writer = WriterType::New();
        writer->SetInput(rescaleFilter->GetOutput());
        writer->SetFileName("patch.png");
        writer->Update();
    }

    // Extract the best matching patch
    FloatImageType::IndexType bestPatchStart;
    bestPatchStart[0] = maximumCorrelationPatchCenter[0] - radius[0];
    bestPatchStart[1] = maximumCorrelationPatchCenter[1] - radius[1];

    FloatImageType::RegionType bestPatchRegion(bestPatchStart,patchSize);

    ExtractFilterType::Pointer bestPatchExtractFilter = ExtractFilterType::New();
    bestPatchExtractFilter->SetRegionOfInterest(bestPatchRegion);
    bestPatchExtractFilter->SetInput(reader->GetOutput());
    bestPatchExtractFilter->Update();

#ifdef ENABLE_QUICKVIEW
    QuickView viewer;
    viewer.AddImage(reader->GetOutput());
    viewer.AddImage(extractFilter->GetOutput());
    viewer.AddImage(correlationFilter->GetOutput());
    viewer.AddImage(bestPatchExtractFilter->GetOutput());
    viewer.Visualize();
#endif

    return EXIT_SUCCESS;
}
