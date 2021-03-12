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

if len(sys.argv) != 4:
    print(
        "Usage: "
        + sys.argv[0]
        + " <InputFileName> <DisplacementFieldFileName> <OutputFileName>"
    )
    sys.exit(1)

inputFileName = sys.argv[1]
displacementFieldFileName = sys.argv[2]
outputFileName = sys.argv[3]

Dimension = 2

VectorComponentType = itk.F
VectorPixelType = itk.Vector[VectorComponentType, Dimension]

DisplacementFieldType = itk.Image[VectorPixelType, Dimension]

PixelType = itk.UC
ImageType = itk.Image[PixelType, Dimension]

reader = itk.ImageFileReader[ImageType].New()
reader.SetFileName(inputFileName)

fieldReader = itk.ImageFileReader[DisplacementFieldType].New()
fieldReader.SetFileName(displacementFieldFileName)
fieldReader.Update()

deformationField = fieldReader.GetOutput()

warpFilter = itk.WarpImageFilter[ImageType, ImageType, DisplacementFieldType].New()

interpolator = itk.LinearInterpolateImageFunction[ImageType, itk.D].New()

warpFilter.SetInterpolator(interpolator)

warpFilter.SetOutputSpacing(deformationField.GetSpacing())
warpFilter.SetOutputOrigin(deformationField.GetOrigin())
warpFilter.SetOutputDirection(deformationField.GetDirection())

warpFilter.SetDisplacementField(deformationField)

warpFilter.SetInput(reader.GetOutput())

writer = itk.ImageFileWriter[ImageType].New()
writer.SetInput(warpFilter.GetOutput())
writer.SetFileName(outputFileName)

writer.Update()
