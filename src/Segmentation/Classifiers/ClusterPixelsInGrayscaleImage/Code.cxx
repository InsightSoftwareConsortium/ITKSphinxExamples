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
#include "itkScalarImageKmeansImageFilter.h"
#include "itkRelabelComponentImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkImageRegionIterator.h"

#include <itkImageToVTKImageFilter.h>

#include "vtkVersion.h"
#include "vtkImageViewer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkImageActor.h"
#include "vtkImageMapper3D.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRenderer.h"

using ImageType = itk::Image<unsigned char, 2>;

static void
CreateImage(ImageType::Pointer image);

int
main()
{
  ImageType::Pointer image = ImageType::New();
  CreateImage(image);

  using KMeansFilterType = itk::ScalarImageKmeansImageFilter<ImageType>;

  KMeansFilterType::Pointer kmeansFilter = KMeansFilterType::New();

  kmeansFilter->SetInput(image);
  kmeansFilter->SetUseNonContiguousLabels(true);
  kmeansFilter->AddClassWithInitialMean(8);
  kmeansFilter->AddClassWithInitialMean(110);
  kmeansFilter->AddClassWithInitialMean(210);
  kmeansFilter->Update();

  KMeansFilterType::ParametersType estimatedMeans = kmeansFilter->GetFinalMeans();

  const unsigned int numberOfClasses = estimatedMeans.Size();

  for (unsigned int i = 0; i < numberOfClasses; ++i)
  {
    std::cout << "cluster[" << i << "] ";
    std::cout << "    estimated mean : " << estimatedMeans[i] << std::endl;
  }

  using OutputImageType = KMeansFilterType::OutputImageType;

  using RelabelFilterType = itk::RelabelComponentImageFilter<OutputImageType, OutputImageType>;

  RelabelFilterType::Pointer relabeler = RelabelFilterType::New();

  relabeler->SetInput(kmeansFilter->GetOutput());

  using RescaleFilterType = itk::RescaleIntensityImageFilter<ImageType, ImageType>;
  RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
  rescaleFilter->SetInput(relabeler->GetOutput());
  rescaleFilter->SetOutputMinimum(0);
  rescaleFilter->SetOutputMaximum(255);

  using SizesType = RelabelFilterType::ObjectSizeInPixelsContainerType;

  const SizesType & sizes = relabeler->GetSizeOfObjectsInPixels();

  auto sizeItr = sizes.begin();
  auto sizeEnd = sizes.end();

  std::cout << "Number of pixels per class " << std::endl;
  unsigned int kclass = 0;
  while (sizeItr != sizeEnd)
  {
    std::cout << "Class " << kclass << " = " << *sizeItr << std::endl;
    ++kclass;
    ++sizeItr;
  }

  // Visualize
  using ConnectorType = itk::ImageToVTKImageFilter<ImageType>;
  ConnectorType::Pointer originalConnector = ConnectorType::New();
  originalConnector->SetInput(image);
  vtkSmartPointer<vtkImageActor> originalActor = vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  originalActor->SetInput(originalConnector->GetOutput());
#else
  originalConnector->Update();
  originalActor->SetInputData(originalConnector->GetOutput());
#endif

  ConnectorType::Pointer outputConnector = ConnectorType::New();
  outputConnector->SetInput(rescaleFilter->GetOutput());

  vtkSmartPointer<vtkImageActor> outputActor = vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  outputActor->SetInput(outputConnector->GetOutput());
#else
  outputConnector->Update();
  outputActor->SetInputData(outputConnector->GetOutput());
#endif

  // There will be one render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
  double rightViewport[4] = { 0.5, 0.0, 1.0, 1.0 };

  // Setup both renderers
  vtkSmartPointer<vtkRenderer> leftRenderer = vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);
  leftRenderer->SetBackground(.6, .5, .4);

  vtkSmartPointer<vtkRenderer> rightRenderer = vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(.4, .5, .6);


  // Add the sphere to the left and the cube to the right
  leftRenderer->AddActor(originalActor);
  rightRenderer->AddActor(outputActor);

  leftRenderer->ResetCamera();
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

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    if (imageIterator.GetIndex()[0] > 100 && imageIterator.GetIndex()[0] < 150 && imageIterator.GetIndex()[1] > 100 &&
        imageIterator.GetIndex()[1] < 150)
    {
      imageIterator.Set(100);
    }
    else if (imageIterator.GetIndex()[0] > 50 && imageIterator.GetIndex()[0] < 70 && imageIterator.GetIndex()[1] > 50 &&
             imageIterator.GetIndex()[1] < 70)
    {
      imageIterator.Set(200);
    }
    else
    {
      imageIterator.Set(10);
    }

    ++imageIterator;
  }
}
