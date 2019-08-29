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
#include <itkImage.h>

#include <itkVTKImageToImageFilter.h>

#include "vtkSmartPointer.h"
#include "vtkPNGReader.h"
#include <vtkImageLuminance.h>

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Required: filename" << std::endl;
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName(argv[1]);
  // reader->SetNumberOfScalarComponents(1); //doesn't seem to work - use ImageLuminance instead
  reader->Update();


  // Must convert image to grayscale because itkVTKImageToImageFilter only accepts single channel images
  vtkSmartPointer<vtkImageLuminance> luminanceFilter = vtkSmartPointer<vtkImageLuminance>::New();
  luminanceFilter->SetInputConnection(reader->GetOutputPort());
  luminanceFilter->Update();

  using ImageType = itk::Image<unsigned char, 2>;

  using VTKImageToImageType = itk::VTKImageToImageFilter<ImageType>;

  VTKImageToImageType::Pointer vtkImageToImageFilter = VTKImageToImageType::New();
  vtkImageToImageFilter->SetInput(luminanceFilter->GetOutput());
  // vtkImageToImageFilter->SetInput(reader->GetOutput());
  vtkImageToImageFilter->Update();

  ImageType::Pointer image = ImageType::New();
  image->Graft(vtkImageToImageFilter->GetOutput()); // Need to do this because QuickView can't accept const

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(image.GetPointer()); // Need to do this because QuickView can't accept smart pointers
  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}
