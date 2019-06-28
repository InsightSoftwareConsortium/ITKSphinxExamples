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
#include "itkNormalizeImageFilter.h"
#include "itkStatisticsImageFilter.h"

#ifdef ENABLE_QUICKVIEW
#include "QuickView.h"
#endif

#include <iomanip>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
        return EXIT_FAILURE;
    }

    using FloatImageType = itk::Image<double, 2>;

    using ReaderType = itk::ImageFileReader<FloatImageType>;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(argv[1]);

    using NormalizeFilterType = itk::NormalizeImageFilter< FloatImageType, FloatImageType >;
    NormalizeFilterType::Pointer normalizeFilter = NormalizeFilterType::New();
    normalizeFilter->SetInput(reader->GetOutput());

    using StatisticsFilterType = itk::StatisticsImageFilter< FloatImageType >;
    StatisticsFilterType::Pointer statistics1 = StatisticsFilterType::New();
    statistics1->SetInput(reader->GetOutput());

    StatisticsFilterType::Pointer statistics2 = StatisticsFilterType::New();
    statistics2->SetInput(normalizeFilter->GetOutput());

#ifdef ENABLE_QUICKVIEW
    QuickView viewer;

    std::stringstream desc1;
    statistics1->Update();
    desc1 << itksys::SystemTools::GetFilenameName(argv[1])
          << "\nMean: " << statistics1->GetMean()
          << " Variance: " << statistics1->GetVariance();
    viewer.AddImage(
            reader->GetOutput(),
            true,
            desc1.str());

    std::stringstream desc2;
    statistics2->Update();
    desc2 << "Normalize"
          << "\nMean: "
          << std::fixed << std::setprecision (2) << statistics2->GetMean()
          << " Variance: " << statistics2->GetVariance();
    viewer.AddImage(
            normalizeFilter->GetOutput(),
            true,
            desc2.str());

    viewer.Visualize();
#endif
    return EXIT_SUCCESS;
}

