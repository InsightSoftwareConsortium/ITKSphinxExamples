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
#include "itkImageFileWriter.h"

#include "ImageFilterMultipleOutputs.h"

int main(int, char*[])
{
    // Setup types
    using ImageType = itk::Image<unsigned char, 2>;
    using FilterType = itk::ImageFilterMultipleOutputs<ImageType>;

    // Create and the filter
    FilterType::Pointer filter = FilterType::New();
    filter->Update();

    {
        using WriterType = itk::ImageFileWriter< ImageType  >;
        WriterType::Pointer writer = WriterType::New();
        writer->SetFileName("TestOutput1.jpg");
        writer->SetInput(filter->GetOutput1());
        writer->Update();
    }

    {
        using WriterType = itk::ImageFileWriter< ImageType  >;
        WriterType::Pointer writer = WriterType::New();
        writer->SetFileName("TestOutput2.jpg");
        writer->SetInput(filter->GetOutput2());
        writer->Update();
    }

    return EXIT_SUCCESS;
}

