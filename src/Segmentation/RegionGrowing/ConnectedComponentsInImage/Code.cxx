/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#include "itkConnectedThresholdImageFilter.h"
#include "itkCastImageFilter.h"

#include <itkImageToVTKImageFilter.h>

#include "vtkImageViewer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkImageActor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRenderer.h"

using PixelType = unsigned char;
constexpr size_t Dimension = 3;
using ImageType = itk::Image<PixelType, Dimension>;

static void
CreateImage(ImageType::Pointer image);

int
main(int argc, char * argv[])
{
  auto image = ImageType::New();
  CreateImage(image);

  using ConnectedFilterType = itk::ConnectedThresholdImageFilter<ImageType, ImageType>;
  auto  connectedThreshold = ConnectedFilterType::New();
  float lower = 95.0;
  float upper = 105.0;
  connectedThreshold->SetLower(lower);
  connectedThreshold->SetUpper(upper);

  connectedThreshold->SetReplaceValue(255);

  // Seed 1: (25, 35)
  ImageType::IndexType seed1;
  seed1[0] = 25;
  seed1[1] = 35;
  connectedThreshold->SetSeed(seed1);
  connectedThreshold->SetInput(image);

  // Seed 2: (110, 120)
  ImageType::IndexType seed2;
  seed2[0] = 110;
  seed2[1] = 120;
  connectedThreshold->SetSeed(seed2);
  connectedThreshold->SetReplaceValue(150);

  connectedThreshold->SetInput(image);

  // Visualize
  using ConnectorType = itk::ImageToVTKImageFilter<ImageType>;
  auto connector2 = ConnectorType::New();
  connector2->SetInput(image);

  vtkSmartPointer<vtkImageActor> actor2 = vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  actor2->SetInput(connector->GetOutput());
#else
  connector2->Update();
  actor2->GetMapper()->SetInputData(connector2->GetOutput());
#endif

  // Visualize joined image
  auto addConnector = ConnectorType::New();
  addConnector->SetInput(connectedThreshold->GetOutput());

  vtkSmartPointer<vtkImageActor> addActor = vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  addActor->SetInput(connector->GetOutput());
#else
  addConnector->Update();
  addActor->GetMapper()->SetInputData(addConnector->GetOutput());
#endif

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(900, 300);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = { 0.0, 0.0, 0.33, 1.0 };
  double centerViewport[4] = { 0.33, 0.0, 0.66, 1.0 };
  double rightViewport[4] = { 0.66, 0.0, 1.0, 1.0 };

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer = vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> centerRenderer = vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(centerRenderer);
  centerRenderer->SetViewport(centerViewport);
  centerRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> rightRenderer = vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);

  // Add the sphere to the left and the cube to the right
  leftRenderer->AddActor(actor1);
  centerRenderer->AddActor(actor2);
  rightRenderer->AddActor(addActor);

  leftRenderer->ResetCamera();
  centerRenderer->ResetCamera();
  rightRenderer->ResetCamera();

  renderWindow->Render();

  vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle(style);

  interactor->Start();


  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  // Create an image with 2 connected components
  ImageType::RegionType region;
  ImageType::IndexType  start;
  start[0] = 0;
  start[1] = 0;

  ImageType::SizeType size;
  size[0] = 200;
  size[1] = 300;

  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  // Make a square
  for (unsigned int r = 20; r < 80; ++r)
  {
    for (unsigned int c = 30; c < 100; ++c)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 100.0);
    }
  }

  // Make another square
  for (unsigned int r = 100; r < 130; ++r)
  {
    for (unsigned int c = 115; c < 160; ++c)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 100.0);
    }
  }
}
