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
#include "itkConstNeighborhoodIterator.h"
#include "itkConstantBoundaryCondition.h"
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

using ImageType = itk::Image<unsigned char, 2>;
static void CreateImage(ImageType::Pointer image);

int main(int, char*[])
{
    ImageType::Pointer image = ImageType::New();
    CreateImage(image);

    ImageType::SizeType regionSize;
    regionSize[0] = 50;
    regionSize[1] = 1;

    ImageType::IndexType regionIndex;
    regionIndex[0] = 0;
    regionIndex[1] = 0;

    ImageType::RegionType region;
    region.SetSize(regionSize);
    region.SetIndex(regionIndex);

    ImageType::SizeType radius;
    radius[0] = 1;
    radius[1] = 1;

    using BoundaryConditionType = itk::ConstantBoundaryCondition<ImageType>;
    itk::ConstNeighborhoodIterator<ImageType, BoundaryConditionType> iterator(radius, image,region);

    while(!iterator.IsAtEnd())
    {
        for(unsigned int i = 0; i < 9; i++)
        {
            ImageType::IndexType index = iterator.GetIndex(i);

            std::cout << "Index: " << index
                      << " Pixel: " << i << " = "
                      << (int)iterator.GetPixel(i) << std::endl;
        }
        ++iterator;
    }

    // Visualize
    using ConnectorType = itk::ImageToVTKImageFilter<ImageType>;
    ConnectorType::Pointer connector = ConnectorType::New();
    connector->SetInput(image);

    vtkSmartPointer<vtkImageActor> actor =
            vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
    actor->SetInput(connector->GetOutput());
#else
    connector->Update();
  actor->GetMapper()->SetInputData(connector->GetOutput());
#endif

    vtkSmartPointer<vtkRenderWindow> renderWindow =
            vtkSmartPointer<vtkRenderWindow>::New();

    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    vtkSmartPointer<vtkRenderer> renderer =
            vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    renderer->AddActor(actor);
    renderer->ResetCamera();

    renderWindow->Render();

    vtkSmartPointer<vtkInteractorStyleImage> style =
            vtkSmartPointer<vtkInteractorStyleImage>::New();

    interactor->SetInteractorStyle(style);

    interactor->Start();

    return EXIT_SUCCESS;
}

void CreateImage(ImageType::Pointer image)
{
    // Create an image with 2 connected components
    ImageType::RegionType region;
    ImageType::IndexType start;
    start[0] = 0;
    start[1] = 0;

    ImageType::SizeType size;
    unsigned int NumRows = 5;
    unsigned int NumCols = 5;
    size[0] = NumRows;
    size[1] = NumCols;

    region.SetSize(size);
    region.SetIndex(start);

    image->SetRegions(region);
    image->Allocate();

    itk::ImageRegionIterator<ImageType> imageIterator(image,region);

    // Set all pixels to white
    while(!imageIterator.IsAtEnd())
    {
        imageIterator.Set(255);
        ++imageIterator;
    }
}

