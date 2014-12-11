#!/usr/bin/env python

#=========================================================================
#
#  Copyright Insight Software Consortium
#
#  Licensed under the Apache License, Version 2.0 (the "License")
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http:*www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#=========================================================================

import sys
import itk

from distutils.version import StrictVersion as VS
if VS(itk.Version.GetITKVersion()) < VS("4.7.0"):
   print("ITK 4.7.0 is required (see example documentation).")
   sys.exit(1)

if len(sys.argv) != 5:
    print(
        "Usage: " + sys.argv[0] +
        " [InputFileName] [OutputFileNameX] [OutputFileNameY]" +
        " [OutputFileNameMagnitude]")
    sys.exit(1)

inputFileName = sys.argv[1]
outputFileNameX = sys.argv[2]
outputFileNameY = sys.argv[3]
outputFileNameMagnitude = sys.argv[4]

Dimension = 2

filenames = []
filenames.append(outputFileNameX)
filenames.append(outputFileNameY)

# Input and output are png files, use unsigned char
PixelType = itk.UC
ImageType = itk.Image[PixelType, Dimension]
# Double type for GradientRecursiveGaussianImageFilter
DoublePixelType = itk.D
DoubleImageType = itk.Image[DoublePixelType, Dimension]
# The output of GradientRecursiveGaussianImageFilter
# are images of the gradient along X and Y, so the type of
# the output is a covariant vector of dimension 2 (X, Y)
CovPixelType = itk.CovariantVector[DoublePixelType, Dimension]
CovImageType = itk.Image[CovPixelType, Dimension]

ReaderType = itk.ImageFileReader[ImageType]
reader = ReaderType.New()
reader.SetFileName(inputFileName)

FilterType = itk.GradientRecursiveGaussianImageFilter[ImageType, CovImageType]
gradientFilter = FilterType.New()
gradientFilter.SetInput(reader.GetOutput())

# Allows to select the X or Y output images
IndexSelectionType = itk.VectorIndexSelectionCastImageFilter[
    CovImageType, DoubleImageType]
indexSelectionFilter = IndexSelectionType.New()
indexSelectionFilter.SetInput(gradientFilter.GetOutput())

# Rescale for png output
RescalerType = itk.RescaleIntensityImageFilter[DoubleImageType, ImageType]
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
MagnitudeType = itk.VectorMagnitudeImageFilter[
    CovImageType, DoubleImageType]
magnitudeFilter = MagnitudeType.New()
magnitudeFilter.SetInput(gradientFilter.GetOutput())

# Rescale for png output
rescaler.SetInput(magnitudeFilter.GetOutput())

writer.SetFileName(outputFileNameMagnitude)
writer.SetInput(rescaler.GetOutput())
writer.Update()
