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
#include "itkDerivativeImageFilter.h"

#include "QuickView.h"

int main(int argc, char * argv[])
{
    // Verify command line arguments
    if( argc < 2 )
    {
        std::cerr << "Usage: " << std::endl;
        std::cerr << argv[0] << " inputImageFile" << std::endl;
        return EXIT_FAILURE;
    }

    // Parse command line arguments
    std::string inputFilename = argv[1];

    // Setup types
    using FloatImageType = itk::Image< float,  2 >;
    using UnsignedCharImageType = itk::Image< unsigned char, 2 >;

    using readerType = itk::ImageFileReader< UnsignedCharImageType >;

    using filterType = itk::DerivativeImageFilter<
            UnsignedCharImageType, FloatImageType >;

    // Create and setup a reader
    readerType::Pointer reader = readerType::New();
    reader->SetFileName( inputFilename.c_str() );

    // Create and setup a derivative filter
    filterType::Pointer derivativeFilter = filterType::New();
    derivativeFilter->SetInput( reader->GetOutput() );
    derivativeFilter->SetDirection(0); // "x" axis

    QuickView viewer;

    viewer.AddImage<UnsignedCharImageType>(reader->GetOutput());
    viewer.AddImage<FloatImageType>(derivativeFilter->GetOutput());
    viewer.Visualize();

    return EXIT_SUCCESS;
}
