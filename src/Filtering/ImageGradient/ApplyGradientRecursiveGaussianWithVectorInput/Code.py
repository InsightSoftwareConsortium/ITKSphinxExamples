#!/usr/bin/env python

# Copyright NumFOCUS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#        https://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys
import itk
import argparse

from distutils.version import StrictVersion as VS

if VS(itk.Version.GetITKVersion()) < VS("4.8.0"):
    print("ITK 4.8.0 is required (see example documentation).")
    sys.exit(1)

parser = argparse.ArgumentParser(
    description="Apply Gradient Recursive Gaussian With Vector Input."
)
parser.add_argument("input_image")
parser.add_argument("output_image_1x")
parser.add_argument("output_image_1y")
parser.add_argument("output_image_2x")
parser.add_argument("output_image_2y")
args = parser.parse_args()

filenames = [
    args.output_image_1x,
    args.output_image_1y,
    args.output_image_2x,
    args.output_image_2y,
]

ImageDimension = 2
VectorDimension = 2
CovDimension = 4

PixelType = itk.UC
ImageType = itk.Image[PixelType, ImageDimension]
FloatPixelType = itk.F
FloatImageType = itk.Image[FloatPixelType, ImageDimension]
VecPixelType = itk.Vector[FloatPixelType, VectorDimension]
VecImageType = itk.Image[VecPixelType, ImageDimension]
CovPixelType = itk.CovariantVector[FloatPixelType, CovDimension]
CovImageType = itk.Image[CovPixelType, ImageDimension]

ReaderType = itk.ImageFileReader[ImageType]
reader = ReaderType.New()
reader.SetFileName(args.input_image)

# Invert the input image
InvertType = itk.InvertIntensityImageFilter[ImageType, ImageType]
inverter = InvertType.New()
inverter.SetInput(reader.GetOutput())

# Cast the image to double type.
CasterType = itk.CastImageFilter[ImageType, FloatImageType]
caster = CasterType.New()
caster2 = CasterType.New()

# Create an image, were each pixel has 2 values: first value is the value
# coming from the input image, second value is coming from the inverted
# image
ComposeType = itk.ComposeImageFilter[FloatImageType, VecImageType]
composer = ComposeType.New()
caster.SetInput(reader.GetOutput())
composer.SetInput(0, caster.GetOutput())
caster2.SetInput(inverter.GetOutput())
composer.SetInput(1, caster2.GetOutput())

# Apply the gradient filter on the two images, this will return and image
# with 4 values per pixel: two X and Y gradients
FilterType = itk.GradientRecursiveGaussianImageFilter[VecImageType, CovImageType]
gradientfilter = FilterType.New()
gradientfilter.SetInput(composer.GetOutput())

# Set up the filter to select each gradient
IndexSelectionType = itk.VectorIndexSelectionCastImageFilter[
    CovImageType, FloatImageType
]
indexSelectionFilter = IndexSelectionType.New()
indexSelectionFilter.SetInput(gradientfilter.GetOutput())

# Rescale for png output
RescalerType = itk.RescaleIntensityImageFilter[FloatImageType, ImageType]
rescaler = RescalerType.New()
rescaler.SetOutputMinimum(itk.NumericTraits[PixelType].min())
rescaler.SetOutputMaximum(itk.NumericTraits[PixelType].max())
rescaler.SetInput(indexSelectionFilter.GetOutput())

WriterType = itk.ImageFileWriter[ImageType]
writer = WriterType.New()
writer.SetInput(rescaler.GetOutput())

for i in range(4):
    indexSelectionFilter.SetIndex(i)
    writer.SetFileName(filenames[i])
    writer.Update()
