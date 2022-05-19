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

#include "itkCustomColormapFunction.h"
#include "itkScalarToRGBColormapImageFilter.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCustomColormapFunction.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkRGBPixel.h"
#include "itkMersenneTwisterRandomVariateGenerator.h"


int
main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << " <InputFileName> <OutputFileName>" << std::endl;

    return EXIT_FAILURE;
  }

  using PixelType = unsigned char;
  using RGBPixelType = itk::RGBPixel<unsigned char>;

  using RGBImageType = itk::Image<RGBPixelType, 2>;
  using ImageType = itk::Image<PixelType, 2>;

  const auto input = itk::ReadImage<ImageType>(argv[1]);

  using ColormapType = itk::Function::CustomColormapFunction<PixelType, RGBPixelType>;
  auto colormap = ColormapType::New();

  ColormapType::ChannelType redChannel;
  ColormapType::ChannelType greenChannel;
  ColormapType::ChannelType blueChannel;

  itk::Statistics::MersenneTwisterRandomVariateGenerator::Pointer random =
    itk::Statistics::MersenneTwisterRandomVariateGenerator::New();

  random->SetSeed(0);

  for (unsigned int i = 0; i < 255; ++i)
  {
    redChannel.push_back(static_cast<ColormapType::RealType>(random->GetUniformVariate(0., 1.0)));

    greenChannel.push_back(static_cast<ColormapType::RealType>(random->GetUniformVariate(0., 1.0)));

    blueChannel.push_back(static_cast<ColormapType::RealType>(random->GetUniformVariate(0., 1.0)));
  }

  colormap->SetRedChannel(redChannel);
  colormap->SetGreenChannel(greenChannel);
  colormap->SetBlueChannel(blueChannel);

  using ColormapFilterType = itk::ScalarToRGBColormapImageFilter<ImageType, RGBImageType>;
  auto colormapFilter1 = ColormapFilterType::New();

  colormapFilter1->SetInput(input);
  colormapFilter1->SetColormap(colormap);

  try
  {
    itk::WriteImage(colormapFilter1->GetOutput(), argv[2]);
  }
  catch (const itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
