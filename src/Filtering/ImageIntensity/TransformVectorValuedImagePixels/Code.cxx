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
#include "itkVectorRescaleIntensityImageFilter.h"
#include "itkCastImageFilter.h"

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        std::cerr << "Required: input output" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    using FloatImageType = itk::Image<itk::CovariantVector<float, 3>, 2>;
    using UnsignedCharImageType = itk::Image<itk::CovariantVector<unsigned char, 3>, 2>;

    using ReaderType = itk::ImageFileReader<FloatImageType>;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(inputFilename);
    reader->Update();

    using VectorRescaleFilterType = itk::VectorRescaleIntensityImageFilter<FloatImageType, UnsignedCharImageType>;
    VectorRescaleFilterType::Pointer rescaleFilter = VectorRescaleFilterType::New();
    rescaleFilter->SetInput(reader->GetOutput());
    rescaleFilter->SetOutputMaximumMagnitude(255);
    rescaleFilter->Update();

    using WriterType = itk::ImageFileWriter<UnsignedCharImageType>;
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(outputFilename);
    writer->SetInput(rescaleFilter->GetOutput());
    writer->Update();

    return EXIT_SUCCESS;
}
