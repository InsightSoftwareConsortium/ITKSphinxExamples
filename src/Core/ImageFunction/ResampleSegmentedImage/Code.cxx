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
#include "itkIdentityTransform.h"
#include "itkLabelImageGaussianInterpolateImageFunction.h"
#include "itkNearestNeighborInterpolateImageFunction.h"
#include "itkResampleImageFilter.h"

#include "itkCustomColormapFunction.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkRGBPixel.h"
#include "itkMersenneTwisterRandomVariateGenerator.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

#include <iostream>

using InputPixelType = unsigned short;
using ImageType = itk::Image<InputPixelType, 2>;
using RGBPixelType = itk::RGBPixel<unsigned char>;
using RGBImageType = itk::Image<RGBPixelType, 2>;

using ColormapType = itk::Function::CustomColormapFunction<ImageType::PixelType, RGBImageType::PixelType>;

static void
CreateRandomColormap(unsigned int size, ColormapType::Pointer colormap);

int
main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << " inputImageFile pixelSize" << std::endl;

    return EXIT_FAILURE;
  }
  double spacing = std::stod(argv[2]);

  using ReaderType = itk::ImageFileReader<ImageType>;

  // Identity transform.
  // We don't want any transform on our image except rescaling which is not
  // specified by a transform but by the input/output spacing as we will see
  // later.
  // So no transform will be specified.
  using TransformType = itk::IdentityTransform<double, 2>;

  using GaussianInterpolatorType = itk::LabelImageGaussianInterpolateImageFunction<ImageType, double>;
  using NearestNeighborInterpolatorType = itk::NearestNeighborInterpolateImageFunction<ImageType, double>;

  using ResampleFilterType = itk::ResampleImageFilter<ImageType, ImageType>;

  // Prepare the reader and update it right away to know the sizes beforehand.
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  // Instantiate the transform and specify it should be the identity transform.
  TransformType::Pointer transform = TransformType::New();
  transform->SetIdentity();

  // Instantiate the interpolators
  GaussianInterpolatorType::Pointer gaussianInterpolator = GaussianInterpolatorType::New();
  gaussianInterpolator->SetSigma(1.0);
  gaussianInterpolator->SetAlpha(3.0);

  NearestNeighborInterpolatorType::Pointer nearestNeighborInterpolator = NearestNeighborInterpolatorType::New();

  // Instantiate the resamplers. Wire in the transforms and the interpolators.
  ResampleFilterType::Pointer resizeFilter1 = ResampleFilterType::New();
  resizeFilter1->SetTransform(transform);
  resizeFilter1->SetInterpolator(gaussianInterpolator);

  ResampleFilterType::Pointer resizeFilter2 = ResampleFilterType::New();
  resizeFilter2->SetTransform(transform);
  resizeFilter2->SetInterpolator(nearestNeighborInterpolator);

  //     Compute and set the output size
  //
  //     The computation must be so that the following holds:
  //
  //     new width         old x spacing
  //     ----------   =   ---------------
  //     old width         new x spacing
  //
  //
  //     new height         old y spacing
  //    ------------  =   ---------------
  //     old height         new y spacing
  //
  //     So either we specify new height and width and compute new spacings
  //     or we specify new spacing and compute new height and width
  //     and computations that follows need to be modified a little (as it is
  //     done at step 2 there:
  //       http://itk.org/Wiki/ITK/Examples/DICOM/ResampleDICOM)
  //

  // Fetch original image spacing.
  const ImageType::SpacingType & inputSpacing = reader->GetOutput()->GetSpacing();

  double outputSpacing[2];
  outputSpacing[0] = spacing;
  outputSpacing[1] = spacing;

  // Fetch original image size
  const ImageType::RegionType & inputRegion = reader->GetOutput()->GetLargestPossibleRegion();
  const ImageType::SizeType &   inputSize = inputRegion.GetSize();
  unsigned int                  oldWidth = inputSize[0];
  unsigned int                  oldHeight = inputSize[1];

  unsigned int newWidth = (double)oldWidth * inputSpacing[0] / spacing;
  unsigned int newHeight = (double)oldHeight * inputSpacing[1] / spacing;

  // Set the output spacing as specified on the command line
  resizeFilter1->SetOutputSpacing(outputSpacing);
  resizeFilter2->SetOutputSpacing(outputSpacing);

  // Set the computed size
  itk::Size<2> outputSize = { { newWidth, newHeight } };
  resizeFilter1->SetSize(outputSize);
  resizeFilter2->SetSize(outputSize);

  // Specify the input for the resamplers
  resizeFilter1->SetInput(reader->GetOutput());
  resizeFilter2->SetInput(reader->GetOutput());

  // Display the images
  using ColormapFilterType = itk::ScalarToRGBColormapImageFilter<ImageType, RGBImageType>;
  ColormapFilterType::Pointer colormapFilter1 = ColormapFilterType::New();

  ColormapType::Pointer colormap = ColormapType::New();
  CreateRandomColormap(4096, colormap);

  colormapFilter1->SetInput(reader->GetOutput());
  colormapFilter1->SetColormap(colormap);

  ColormapFilterType::Pointer colormapFilter2 = ColormapFilterType::New();
  colormapFilter2->SetInput(resizeFilter1->GetOutput());
  colormapFilter2->SetColormap(colormap);

  ColormapFilterType::Pointer colormapFilter3 = ColormapFilterType::New();
  colormapFilter3->SetInput(resizeFilter2->GetOutput());
  colormapFilter3->SetColormap(colormap);

#ifdef ENABLE_QUICKVIEW
  std::stringstream desc;
  desc << itksys::SystemTools::GetFilenameName(argv[1]) << ": " << oldWidth << ", " << oldHeight;
  QuickView viewer;
  viewer.AddRGBImage(colormapFilter1->GetOutput(), true, desc.str());

  std::stringstream desc2;
  desc2 << "Gaussian Interpolation: " << newWidth << ", " << newHeight;
  viewer.AddRGBImage(colormapFilter2->GetOutput(), true, desc2.str());

  std::stringstream desc3;
  desc3 << "Nearest Neighbor Interpolation: " << newWidth << ", " << newHeight;
  viewer.AddRGBImage(colormapFilter3->GetOutput(), true, desc3.str());
  viewer.Visualize();
#endif
  return EXIT_SUCCESS;
}

void
CreateRandomColormap(unsigned int size, ColormapType::Pointer colormap)
{
#define LOW .3
  ColormapType::ChannelType                                       redChannel;
  ColormapType::ChannelType                                       greenChannel;
  ColormapType::ChannelType                                       blueChannel;
  itk::Statistics::MersenneTwisterRandomVariateGenerator::Pointer random =
    itk::Statistics::MersenneTwisterRandomVariateGenerator::New();

  random->SetSeed(8775070);
  redChannel.push_back(LOW);
  greenChannel.push_back(LOW);
  blueChannel.push_back(LOW);
  for (unsigned int i = 1; i < size; ++i)
  {
    redChannel.push_back(static_cast<ColormapType::RealType>(random->GetUniformVariate(LOW, 1.0)));
    greenChannel.push_back(static_cast<ColormapType::RealType>(random->GetUniformVariate(LOW, 1.0)));
    blueChannel.push_back(static_cast<ColormapType::RealType>(random->GetUniformVariate(LOW, 1.0)));
  }
  colormap->SetRedChannel(redChannel);
  colormap->SetGreenChannel(greenChannel);
  colormap->SetBlueChannel(blueChannel);
}
