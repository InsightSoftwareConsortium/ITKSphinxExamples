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
#include "itkCovariantVector.h"
#include "itkImageFileReader.h"
#include "itkGradientImageFilter.h"

#include <itkImageToVTKImageFilter.h>

#include "vtkPointData.h"
#include "vtkFloatArray.h"
#include "vtkImageData.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderWindow.h"
#include "vtkSmartPointer.h"
#include "vtkImageActor.h"
#include "vtkActor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRenderer.h"
#include "vtkGlyph3DMapper.h"
#include "vtkArrowSource.h"

static void
VectorImageToVTKImage(itk::Image<itk::CovariantVector<float, 2>, 2>::Pointer vectorImage, vtkImageData * VTKImage);

int
main(int argc, char * argv[])
{
  // Verify command line arguments
  if (argc < 2)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "inputImageFile" << std::endl;
    return EXIT_FAILURE;
  }

  // Parse command line arguments
  std::string inputFileName = argv[1];

  // Setup types
  using FloatImageType = itk::Image<float, 2>;
  using UnsignedCharImageType = itk::Image<unsigned char, 2>;

  const auto input = itk::ReadImage<UnsignedCharImageType>(inputFileName);

  // Create and setup a gradient filter
  using GradientFilterType = itk::GradientImageFilter<UnsignedCharImageType, float>;
  auto gradientFilter = GradientFilterType::New();
  gradientFilter->SetInput(input);
  gradientFilter->Update();

  // Visualize original image
  using ConnectorType = itk::ImageToVTKImageFilter<UnsignedCharImageType>;
  auto originalConnector = ConnectorType::New();
  originalConnector->SetInput(input);

  vtkSmartPointer<vtkImageActor> originalActor = vtkSmartPointer<vtkImageActor>::New();
  originalActor->SetInput(originalConnector->GetOutput());

  // Visualize gradient
  vtkSmartPointer<vtkImageData> gradientImage = vtkSmartPointer<vtkImageData>::New();
  VectorImageToVTKImage(gradientFilter->GetOutput(), gradientImage);

  vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();

  vtkSmartPointer<vtkGlyph3DMapper> gradientMapper = vtkSmartPointer<vtkGlyph3DMapper>::New();
  gradientMapper->ScalingOn();
  gradientMapper->SetScaleFactor(.05);
  gradientMapper->SetSourceConnection(arrowSource->GetOutputPort());
  gradientMapper->SetInputConnection(gradientImage->GetProducerPort());
  gradientMapper->Update();

  vtkSmartPointer<vtkActor> gradientActor = vtkSmartPointer<vtkActor>::New();
  gradientActor->SetMapper(gradientMapper);

  // Visualize
  // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double leftViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
  double rightViewport[4] = { 0.5, 0.0, 1.0, 1.0 };

  // Setup both renderers
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);

  vtkSmartPointer<vtkRenderer> leftRenderer = vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(leftRenderer);
  leftRenderer->SetViewport(leftViewport);

  vtkSmartPointer<vtkRenderer> rightRenderer = vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(rightRenderer);
  rightRenderer->SetViewport(rightViewport);
  rightRenderer->SetBackground(1, 0, 0);

  leftRenderer->AddActor(originalActor);
  rightRenderer->AddActor(gradientActor);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

void
VectorImageToVTKImage(itk::Image<itk::CovariantVector<float, 2>, 2>::Pointer vectorImage, vtkImageData * VTKImage)
{
  itk::Image<itk::CovariantVector<float, 2>, 2>::RegionType region = vectorImage->GetLargestPossibleRegion();
  itk::Image<itk::CovariantVector<float, 2>, 2>::SizeType   imageSize = region.GetSize();
  VTKImage->SetExtent(0, imageSize[0] - 1, 0, imageSize[1] - 1, 0, 0);

  vtkSmartPointer<vtkFloatArray> vectors = vtkSmartPointer<vtkFloatArray>::New();
  vectors->SetNumberOfComponents(3);
  vectors->SetNumberOfTuples(imageSize[0] * imageSize[1]);
  vectors->SetName("GradientVectors");

  int counter = 0;
  for (unsigned int j = 0; j < imageSize[1]; j++)
  {
    for (unsigned int i = 0; i < imageSize[0]; i++)
    {
      itk::Image<itk::CovariantVector<float, 2>, 2>::IndexType index;
      index[0] = i;
      index[1] = j;

      itk::Image<itk::CovariantVector<float, 2>, 2>::PixelType pixel = vectorImage->GetPixel(index);

      float v[2];
      v[0] = pixel[0];
      v[1] = pixel[1];
      v[2] = 0;
      vectors->InsertTupleValue(counter, v);
      counter++;
    }
  }
  // std::cout << region << std::endl;

  VTKImage->GetPointData()->SetVectors(vectors);
}
