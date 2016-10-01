#!/usr/bin/env python

#==========================================================================
#
#   Copyright Insight Software Consortium
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================*/

import sys
import itk

if len(sys.argv) != 4:
    print("Usage: " + sys.argv[0] + " <inputImage> <outputImage> <scale>")
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]
scale = float(sys.argv[3])

PixelType = itk.UC
ScalarType = itk.D
Dimension = 2

ImageType = itk.Image[PixelType, Dimension]

ReaderType = itk.ImageFileReader[ImageType]
reader = ReaderType.New()
reader.SetFileName(inputImage)
reader.Update()

inputImage = reader.GetOutput()

size = inputImage.GetLargestPossibleRegion().GetSize()
spacing = inputImage.GetSpacing()

centralPixel = itk.Index[Dimension]()
centralPixel[0] = int(size[0] / 2)
centralPixel[1] = int(size[1] / 2)
centralPoint = itk.Point[ScalarType, Dimension]()
centralPoint[0] = centralPixel[0]
centralPoint[1] = centralPixel[1]

scaleTransform = itk.ScaleTransform[ScalarType, Dimension].New()

parameters = scaleTransform.GetParameters()
parameters[0] = scale
parameters[1] = scale

scaleTransform.SetParameters(parameters)
scaleTransform.SetCenter(centralPoint)

interpolatorType = itk.LinearInterpolateImageFunction[ImageType, ScalarType]
interpolator = interpolatorType.New()

resamplerType = itk.ResampleImageFilter[ImageType, ImageType]
resampleFilter = resamplerType.New()

resampleFilter.SetInput(inputImage)
resampleFilter.SetTransform(scaleTransform)
resampleFilter.SetInterpolator(interpolator)
resampleFilter.SetSize(size)
resampleFilter.SetOutputSpacing(spacing)

WriterType = itk.ImageFileWriter[ImageType]
writer = WriterType.New()
writer.SetFileName(outputImage)
writer.SetInput(resampleFilter.GetOutput())

writer.Update()
