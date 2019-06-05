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
/*
 * #include <itkRandomImageSource.h>
#include "itkImageToVTKImageFilter.h"

#include "vtkVersion.h"
#include <vtkSmartPointer.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolumeProperty.h>
#include <vtkMatrix4x4.h>
#include <vtkAxesActor.h>

using VisualizingImageType = itk::Image<unsigned char, 3>;

VisualizingImageType::Pointer createImage()
{
    itk::Size<3> size;
    size[0]=512;
    size[1]=512;
    size[2]=16;

    itk::RandomImageSource<VisualizingImageType>::Pointer randomImageSource =
        itk::RandomImageSource<VisualizingImageType>::New();
    randomImageSource->SetNumberOfThreads(1); // to produce non-random results
    randomImageSource->SetSize(size);
    randomImageSource->Update();

    VisualizingImageType::Pointer image=randomImageSource->GetOutput();
    double t[3]={0, -200, 150};
    image->SetOrigin(t);
    t[0]=0.68;
    t[1]=0.68;
    t[2]=4.4;
    image->SetSpacing(t);

    VisualizingImageType::DirectionType m;
    m(0,0)=0;
    m(0,1)=1;
    m(0,2)=0;
    m(1,0)=0.707;
    m(1,1)=0;
    m(1,2)=-0.707;
    m(2,0)=-0.707;
    m(2,1)=0;
    m(2,2)=-0.707;
    m=m.GetTranspose();
    image->SetDirection(m);
    return image;
}

int main(int argc, char *argv[])
{
  VisualizingImageType::Pointer image=createImage();

  vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
  vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(0.5f,0.5f,1.0f);

  renWin->AddRenderer(ren1);
  renWin->SetSize(1280,1024);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  renWin->Render(); // make sure we have an OpenGL context.

  using itkVtkConverter = itk::ImageToVTKImageFilter<VisualizingImageType>;
  itkVtkConverter::Pointer conv=itkVtkConverter::New();
  conv->SetInput(image);

  vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper =
      vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  volumeMapper->SetInput(conv->GetOutput());
#else
  conv->Update();
  volumeMapper->SetInputData(conv->GetOutput());
#endif

  vtkSmartPointer<vtkVolumeProperty> volumeProperty =
  vtkSmartPointer<vtkVolumeProperty>::New();

  vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =
  vtkSmartPointer<vtkPiecewiseFunction>::New();
  compositeOpacity->AddPoint(0.0,0.1);
  compositeOpacity->AddPoint(80.0,0.2);
  compositeOpacity->AddPoint(255.0,0.1);
  volumeProperty->SetScalarOpacity(compositeOpacity);

  vtkSmartPointer<vtkColorTransferFunction> color =
  vtkSmartPointer<vtkColorTransferFunction>::New();
  color->AddRGBPoint(0.0  ,0.0,0.0,1.0);
  color->AddRGBPoint(40.0  ,1.0,0.0,0.0);
  color->AddRGBPoint(255.0,1.0,1.0,1.0);
  volumeProperty->SetColor(color);

  vtkSmartPointer<vtkVolume> volume =
  vtkSmartPointer<vtkVolume>::New();
  volume->SetMapper(volumeMapper);
  volume->SetProperty(volumeProperty);

  // Here we take care of position and orientation
  // so that volume is in DICOM patient physical space
  VisualizingImageType::DirectionType d=image->GetDirection();
  vtkMatrix4x4 *mat=vtkMatrix4x4::New(); //start with identity matrix
  for (int i=0; i<3; i++)
      for (int k=0; k<3; k++)
          mat->SetElement(i,k, d(i,k));

  // Counteract the built-in translation by origin
  VisualizingImageType::PointType origin=image->GetOrigin();
  volume->SetPosition(-origin[0], -origin[1], -origin[2]);

  // Add translation to the user matrix
  for (int i=0; i<3; i++)
    {
    mat->SetElement(i,3, origin[i]);
    }
  volume->SetUserMatrix(mat);

  // Add coordinate system axes, so we have a reference for position and orientation
  vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
  axes->SetTotalLength(250,250,250);
  axes->SetShaftTypeToCylinder();
  axes->SetCylinderRadius(0.01);
  ren1->AddActor(axes);

  ren1->AddVolume( volume );
  ren1->ResetCamera();

  renWin->Render();
  renWin->Render();
  renWin->Render();

  iren->Start();

  return EXIT_SUCCESS;
}