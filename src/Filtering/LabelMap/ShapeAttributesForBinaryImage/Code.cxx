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
#include "itkLabelImageToShapeLabelMapFilter.h"

template <typename TImage>
static void
CreateImage(TImage * const image);

int
main(int argc, char * argv[])
{
  constexpr unsigned int Dimension = 2;
  using PixelType = unsigned char;
  using LabelType = unsigned short;
  using InputImageType = itk::Image<PixelType, Dimension>;
  using OutputImageType = itk::Image<LabelType, Dimension>;
  using ShapeLabelObjectType = itk::ShapeLabelObject<LabelType, Dimension>;
  using LabelMapType = itk::LabelMap<ShapeLabelObjectType>;

  std::string             fileName;
  InputImageType::Pointer image;
  if (argc < 2)
  {
    image = InputImageType::New();
    CreateImage(image.GetPointer());
    fileName = "Generated image";
  }
  else
  {
    fileName = argv[1];
    using ReaderType = itk::ImageFileReader<InputImageType>;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(fileName);
    reader->Update();

    image = reader->GetOutput();
  }


  using ConnectedComponentImageFilterType = itk::ConnectedComponentImageFilter<InputImageType, OutputImageType>;
  using I2LType = itk::LabelImageToShapeLabelMapFilter<OutputImageType, LabelMapType>;

  ConnectedComponentImageFilterType::Pointer connected = ConnectedComponentImageFilterType::New();
  connected->SetInput(image);
  connected->Update();

  using I2LType = itk::LabelImageToShapeLabelMapFilter<OutputImageType, LabelMapType>;
  I2LType::Pointer i2l = I2LType::New();
  i2l->SetInput(connected->GetOutput());
  i2l->SetComputePerimeter(true);
  i2l->Update();

  LabelMapType * labelMap = i2l->GetOutput();
  std::cout << "File "
            << "\"" << fileName << "\""
            << " has " << labelMap->GetNumberOfLabelObjects() << " labels." << std::endl;

  // Retrieve all attributes
  for (unsigned int n = 0; n < labelMap->GetNumberOfLabelObjects(); ++n)
  {
    ShapeLabelObjectType * labelObject = labelMap->GetNthLabelObject(n);
    std::cout << "Label: " << itk::NumericTraits<LabelMapType::LabelType>::PrintType(labelObject->GetLabel())
              << std::endl;
    std::cout << "    BoundingBox: " << labelObject->GetBoundingBox() << std::endl;
    std::cout << "    NumberOfPixels: " << labelObject->GetNumberOfPixels() << std::endl;
    std::cout << "    PhysicalSize: " << labelObject->GetPhysicalSize() << std::endl;
    std::cout << "    Centroid: " << labelObject->GetCentroid() << std::endl;
    std::cout << "    NumberOfPixelsOnBorder: " << labelObject->GetNumberOfPixelsOnBorder() << std::endl;
    std::cout << "    PerimeterOnBorder: " << labelObject->GetPerimeterOnBorder() << std::endl;
    std::cout << "    FeretDiameter: " << labelObject->GetFeretDiameter() << std::endl;
    std::cout << "    PrincipalMoments: " << labelObject->GetPrincipalMoments() << std::endl;
    std::cout << "    PrincipalAxes: " << labelObject->GetPrincipalAxes() << std::endl;
    std::cout << "    Elongation: " << labelObject->GetElongation() << std::endl;
    std::cout << "    Perimeter: " << labelObject->GetPerimeter() << std::endl;
    std::cout << "    Roundness: " << labelObject->GetRoundness() << std::endl;
    std::cout << "    EquivalentSphericalRadius: " << labelObject->GetEquivalentSphericalRadius() << std::endl;
    std::cout << "    EquivalentSphericalPerimeter: " << labelObject->GetEquivalentSphericalPerimeter() << std::endl;
    std::cout << "    EquivalentEllipsoidDiameter: " << labelObject->GetEquivalentEllipsoidDiameter() << std::endl;
    std::cout << "    Flatness: " << labelObject->GetFlatness() << std::endl;
    std::cout << "    PerimeterOnBorderRatio: " << labelObject->GetPerimeterOnBorderRatio() << std::endl;
  }

  return EXIT_SUCCESS;
}

template <typename TImage>
void
CreateImage(TImage * const image)
{
  // Create an image with 2 objects
  typename TImage::IndexType start = { { 0, 0 } };
  start[0] = 0;
  start[1] = 0;

  typename TImage::SizeType size;
  unsigned int              NumRows = 200;
  unsigned int              NumCols = 300;
  size[0] = NumRows;
  size[1] = NumCols;

  typename TImage::RegionType region(start, size);

  image->SetRegions(region);
  image->Allocate();

  // Make a square
  for (typename TImage::IndexValueType r = 20; r < 80; ++r)
  {
    for (typename TImage::IndexValueType c = 30; c < 100; ++c)
    {
      typename TImage::IndexType pixelIndex = { { r, c } };

      image->SetPixel(pixelIndex, 255);
    }
  }

  // Make another square
  for (typename TImage::IndexValueType r = 100; r < 130; ++r)
  {
    for (typename TImage::IndexValueType c = 115; c < 160; ++c)
    {
      typename TImage::IndexType pixelIndex = { { r, c } };

      image->SetPixel(pixelIndex, 255);
    }
  }
}
