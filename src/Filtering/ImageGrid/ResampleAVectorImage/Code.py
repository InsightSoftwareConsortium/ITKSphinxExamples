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

from distutils.version import StrictVersion as VS
if VS(itk.Version.GetITKVersion()) < VS("4.7.0"):
    print("ITK 4.7.0 is required (see example documentation).")
    sys.exit(1)

if len(sys.argv) != 3:
    print("Usage: " + sys.argv[0] + " [inputImage] [outputImage]")
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]

Dimension = 2

PixelType = itk.RGBPixel[itk.UC]
ImageType = itk.Image[PixelType, Dimension]

ReaderType = itk.ImageFileReader[ImageType]
reader = ReaderType.New()
reader.SetFileName(inputImage)

filterType = itk.ResampleImageFilter[ImageType, ImageType]
resampleImageFilter = filterType.New()

interpolatorType = itk.LinearInterpolateImageFunction[ImageType, itk.D]
interpolator = interpolatorType.New()

resampleImageFilter.SetInterpolator(interpolator)

transformType = itk.IdentityTransform[itk.D, Dimension]
transform = transformType.New()

resampleImageFilter.SetTransform(transform)

resampleImageFilter.SetDefaultPixelValue([50, 50, 50])
resampleImageFilter.SetOutputSpacing([0.5, 0.5])
resampleImageFilter.SetOutputOrigin([30, 40])

resampleImageFilter.SetSize([300, 300])
resampleImageFilter.SetInput(reader.GetOutput())

WriterType = itk.ImageFileWriter[ImageType]
writer = WriterType.New()
writer.SetFileName(outputImage)
writer.SetInput(resampleImageFilter.GetOutput())
writer.Update()
