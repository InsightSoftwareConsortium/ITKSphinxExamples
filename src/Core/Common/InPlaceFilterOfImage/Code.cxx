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
#include "itkBinaryThresholdImageFilter.h"

#include <itkImageToVTKImageFilter.h>

#include "vtkVersion.h"

#include "vtkSmartPointer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageActor.h"
#include "vtkImageMapper3D.h"
#include "vtkImageViewer.h"

using ImageType = itk::Image<unsigned char, 2>;

static void
ApplyThresholding(ImageType::Pointer image);

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Required: filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  using ReaderType = itk::ImageFileReader<ImageType>;
  ReaderType::Pointer reader = ReaderType::New();

  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  ImageType::Pointer image = reader->GetOutput();

  ApplyThresholding(image);

  // Visualize
  using ConnectorType = itk::ImageToVTKImageFilter<ImageType>;
  ConnectorType::Pointer connector = ConnectorType::New();
  connector->SetInput(image);

  vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  actor->SetInput(connector->GetOutput());
#else
  connector->Update();
  actor->GetMapper()->SetInputData(connector->GetOutput());
#endif

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

  vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(renderer);

  renderer->AddActor(actor);
  renderer->ResetCamera();

  renderWindow->Render();

  vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();

  interactor->SetInteractorStyle(style);

  interactor->Start();

  return EXIT_SUCCESS;
}

void
ApplyThresholding(ImageType::Pointer image)
{

  using BinaryThresholdImageFilterType = itk::BinaryThresholdImageFilter<ImageType, ImageType>;

  BinaryThresholdImageFilterType::Pointer thresholdFilter = BinaryThresholdImageFilterType::New();
  thresholdFilter->SetInput(image);
  thresholdFilter->SetLowerThreshold(10);
  thresholdFilter->SetUpperThreshold(50);
  thresholdFilter->SetInsideValue(255);
  thresholdFilter->SetOutsideValue(0);
  thresholdFilter->InPlaceOn();
  thresholdFilter->Update();
}
