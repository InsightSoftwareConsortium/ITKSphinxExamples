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
#include "itkConnectedComponentImageFilter.h"
#include "itkLabelShapeKeepNObjectsImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

#include "itksys/SystemTools.hxx"
#include <sstream>

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage:" << std::endl;
    std::cout << argv[0] << " InputFileName" << std::endl;
  }
  constexpr unsigned int Dimension = 2;
  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;

  const auto input = itk::ReadImage<ImageType>(argv[1]);

  using OutputImageType = itk::Image<unsigned short, Dimension>;

  using ConnectedComponentImageFilterType = itk::ConnectedComponentImageFilter<ImageType, OutputImageType>;

  auto connected = ConnectedComponentImageFilterType::New();
  connected->SetInput(input);
  connected->Update();

  std::cout << "Number of objects: " << connected->GetObjectCount() << std::endl;

  using LabelShapeKeepNObjectsImageFilterType = itk::LabelShapeKeepNObjectsImageFilter<OutputImageType>;
  LabelShapeKeepNObjectsImageFilterType::Pointer labelShapeKeepNObjectsImageFilter =
    LabelShapeKeepNObjectsImageFilterType::New();
  labelShapeKeepNObjectsImageFilter->SetInput(connected->GetOutput());
  labelShapeKeepNObjectsImageFilter->SetBackgroundValue(0);
  labelShapeKeepNObjectsImageFilter->SetNumberOfObjects(1);
  labelShapeKeepNObjectsImageFilter->SetAttribute(
    LabelShapeKeepNObjectsImageFilterType::LabelObjectType::NUMBER_OF_PIXELS);

  using RescaleFilterType = itk::RescaleIntensityImageFilter<OutputImageType, ImageType>;
  auto rescaleFilter = RescaleFilterType::New();
  rescaleFilter->SetOutputMinimum(0);
  rescaleFilter->SetOutputMaximum(itk::NumericTraits<PixelType>::max());
  rescaleFilter->SetInput(labelShapeKeepNObjectsImageFilter->GetOutput());

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(input.GetPointer(), true, itksys::SystemTools::GetFilenameName(argv[1]));

  std::stringstream desc;
  desc << "Largest object of " << connected->GetObjectCount() << " objects";
  viewer.AddImage(rescaleFilter->GetOutput(), true, desc.str());

  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}
