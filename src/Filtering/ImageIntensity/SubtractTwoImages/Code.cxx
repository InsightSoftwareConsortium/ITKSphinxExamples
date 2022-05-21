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
#include "itkRescaleIntensityImageFilter.h"
#include "itkSubtractImageFilter.h"

#include "itkImageToVTKImageFilter.h"

#include "vtkVersion.h"
#include "vtkImageViewer.h"
#include "vtkImageMapper3D.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkImageActor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRenderer.h"

using ImageType = itk::Image<unsigned char, 2>;

static void
CreateImage1(ImageType::Pointer image);
static void
CreateImage2(ImageType::Pointer image);

int
main()
{
  auto image1 = ImageType::New();
  CreateImage1(image1);

  auto image2 = ImageType::New();
  CreateImage2(image2);

  using SubtractImageFilterType = itk::SubtractImageFilter<ImageType, ImageType>;

  auto subtractFilter = SubtractImageFilterType::New();
  subtractFilter->SetInput1(image1);
  subtractFilter->SetInput2(image2);
  subtractFilter->Update();

  // Visualize first image
  using ConnectorType = itk::ImageToVTKImageFilter<ImageType>;
  auto connector1 = ConnectorType::New();
  connector1->SetInput(image1);

  vtkSmartPointer<vtkImageActor> actor1 = vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  actor1->SetInput(connector1->GetOutput());
#else
  connector1->Update();
  actor1->GetMapper()->SetInputData(connector1->GetOutput());
#endif

  // Visualize second image
  using ConnectorType = itk::ImageToVTKImageFilter<ImageType>;
  auto connector2 = ConnectorType::New();
  connector2->SetInput(image2);

  vtkSmartPointer<vtkImageActor> actor2 = vtkSmartPointer<vtkImageActor>::New();

#if VTK_MAJOR_VERSION <= 5
  actor2->SetInput(connector2->GetOutput());
#else
  connector2->Update();
  actor2->GetMapper()->SetInputData(connector2->GetOutput());
#endif

  // Visualize subtracted image
  auto subtractConnector = ConnectorType::New();
  subtractConnector->SetInput(subtractFilter->GetOutput());

  vtkSmartPointer<vtkImageActor> subtractActor = vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  subtractActor->SetInput(subtractConnector->GetOutput());
#else
  subtractConnector->Update();
  subtractActor->GetMapper()->SetInputData(subtractConnector->GetOutput());
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
  rightRenderer->AddActor(subtractActor);

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
CreateImage1(ImageType::Pointer image)
{
  // Create an image with 2 connected components
  ImageType::RegionType region;
  ImageType::IndexType  start;
  start[0] = 0;
  start[1] = 0;

  ImageType::SizeType size;
  unsigned int        NumRows = 200;
  unsigned int        NumCols = 300;
  size[0] = NumRows;
  size[1] = NumCols;

  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  // Make a square
  for (unsigned int r = 20; r < 80; ++r)
  {
    for (unsigned int c = 20; c < 80; ++c)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 15);
    }
  }
}


void
CreateImage2(ImageType::Pointer image)
{
  // Create an image with 2 connected components
  ImageType::RegionType region;
  ImageType::IndexType  start;
  start[0] = 0;
  start[1] = 0;

  ImageType::SizeType size;
  unsigned int        NumRows = 200;
  unsigned int        NumCols = 300;
  size[0] = NumRows;
  size[1] = NumCols;

  region.SetSize(size);
  region.SetIndex(start);

  image->SetRegions(region);
  image->Allocate();

  // Make another square
  for (unsigned int r = 40; r < 100; ++r)
  {
    for (unsigned int c = 40; c < 100; ++c)
    {
      ImageType::IndexType pixelIndex;
      pixelIndex[0] = r;
      pixelIndex[1] = c;

      image->SetPixel(pixelIndex, 15);
    }
  }
}
