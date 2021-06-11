#!/usr/bin/env python

# Copyright NumFOCUS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0.txt
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

if VS(itk.Version.GetITKVersion()) < VS("4.7.0"):
    print("ITK 4.7.0 is required (see example documentation).")
    sys.exit(1)

parser = argparse.ArgumentParser(description="Apply Gradient Recursive Gaussian.")
parser.add_argument("input_image")
parser.add_argument("output_image_x")
parser.add_argument("output_image_y")
parser.add_argument("output_image_magnitude")
args = parser.parse_args()

Dimension = 2

filenames = []
filenames.append(args.output_image_x)
filenames.append(args.output_image_y)

# Input and output are png files, use unsigned char
PixelType = itk.UC
ImageType = itk.Image[PixelType, Dimension]
# Float type for GradientRecursiveGaussianImageFilter
FloatPixelType = itk.F
FloatImageType = itk.Image[FloatPixelType, Dimension]
# The output of GradientRecursiveGaussianImageFilter
# are images of the gradient along X and Y, so the type of
# the output is a covariant vector of dimension 2 (X, Y)
CovPixelType = itk.CovariantVector[FloatPixelType, Dimension]
CovImageType = itk.Image[CovPixelType, Dimension]

ReaderType = itk.ImageFileReader[ImageType]
reader = ReaderType.New()
reader.SetFileName(args.input_image)

FilterType = itk.GradientRecursiveGaussianImageFilter[ImageType, CovImageType]
gradientFilter = FilterType.New()
gradientFilter.SetInput(reader.GetOutput())

# Allows to select the X or Y output images
IndexSelectionType = itk.VectorIndexSelectionCastImageFilter[
    CovImageType, FloatImageType
]
indexSelectionFilter = IndexSelectionType.New()
indexSelectionFilter.SetInput(gradientFilter.GetOutput())

# Rescale for png output
RescalerType = itk.RescaleIntensityImageFilter[FloatImageType, ImageType]
rescaler = RescalerType.New()
rescaler.SetOutputMinimum(itk.NumericTraits[PixelType].min())
rescaler.SetOutputMaximum(itk.NumericTraits[PixelType].max())
rescaler.SetInput(indexSelectionFilter.GetOutput())

WriterType = itk.ImageFileWriter[ImageType]
writer = WriterType.New()
writer.SetInput(rescaler.GetOutput())

# Write the X and Y images
for i in range(2):
    writer.SetFileName(filenames[i])
    indexSelectionFilter.SetIndex(i)
    writer.Update()

# Compute the magnitude of the vector and output the image
MagnitudeType = itk.VectorMagnitudeImageFilter[CovImageType, FloatImageType]
magnitudeFilter = MagnitudeType.New()
magnitudeFilter.SetInput(gradientFilter.GetOutput())

# Rescale for png output
rescaler.SetInput(magnitudeFilter.GetOutput())

writer.SetFileName(args.output_image_magnitude)
writer.SetInput(rescaler.GetOutput())
writer.Update()
