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
#include "itkImageFileReader.h"
#include "itkFlatStructuringElement.h"
#include "itkBinaryErodeImageFilter.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << argv[0] << " InputImageFile [radius]" << std::endl;
    return EXIT_FAILURE;
  }

  unsigned int radius = 2;
  if (argc > 2)
  {
    radius = std::stoi(argv[2]);
  }

  using ImageType = itk::Image<unsigned char, 2>;
  using ReaderType = itk::ImageFileReader<ImageType>;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(argv[1]);

  using StructuringElementType = itk::FlatStructuringElement<2>;
  StructuringElementType::RadiusType elementRadius;
  elementRadius.Fill(radius);

  StructuringElementType structuringElement = StructuringElementType::Box(elementRadius);

  using BinaryErodeImageFilterType = itk::BinaryErodeImageFilter<ImageType, ImageType, StructuringElementType>;

  BinaryErodeImageFilterType::Pointer erodeFilter = BinaryErodeImageFilterType::New();
  erodeFilter->SetInput(reader->GetOutput());
  erodeFilter->SetKernel(structuringElement);
  erodeFilter->SetErodeValue(255);

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(reader->GetOutput());
  viewer.AddImage(erodeFilter->GetOutput());
  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}
