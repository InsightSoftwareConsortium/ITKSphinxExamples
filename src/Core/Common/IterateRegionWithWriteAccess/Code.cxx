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
#include "itkImageFileReader.h"
#include "itkImageRegionIterator.h"

#include <itkImageToVTKImageFilter.h>

#include "vtkVersion.h"
#include "vtkImageViewer.h"
#include "vtkImageMapper3D.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"
#include "vtkImageActor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRenderer.h"

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Required: filename" << std::endl;
    return EXIT_FAILURE;
  }

  using ImageType = itk::Image<unsigned char, 2>;

  ImageType::Pointer image = itk::ReadImage<ImageType>(argv[1]);

  ImageType::SizeType regionSize;
  regionSize[0] = 5;
  regionSize[1] = 4;

  ImageType::IndexType regionIndex;
  regionIndex[0] = 0;
  regionIndex[1] = 0;

  ImageType::RegionType region;
  region.SetSize(regionSize);
  region.SetIndex(regionIndex);

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  while (!imageIterator.IsAtEnd())
  {
    // Get the value of the current pixel
    // unsigned char val = imageIterator.Get();
    // std::cout << (int)val << std::endl;

    // Set the current pixel to white
    imageIterator.Set(255);

    ++imageIterator;
  }

  // Visualize
  using ConnectorType = itk::ImageToVTKImageFilter<ImageType>;
  auto connector = ConnectorType::New();
  connector->SetInput(image);

  vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  actor->SetInput(connector->GetOutput());
#else
  connector->Update();
  actor->GetMapper()->SetInputData(connector->GetOutput());
#endif

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
