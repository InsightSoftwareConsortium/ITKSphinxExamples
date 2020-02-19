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

if len(sys.argv) != 3:
    print("Usage: " + sys.argv[0] + " <inputImage> <outputImage> ")
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]

Dimension = 2
InputPixelType = itk.F
OutputPixelType = itk.UC

InputImageType = itk.Image[InputPixelType, Dimension]
OutputImageType = itk.Image[OutputPixelType, Dimension]

reader = itk.ImageFileReader[InputImageType].New()
reader.SetFileName(inputImage)

rescaler = itk.RescaleIntensityImageFilter[
    InputImageType,
    InputImageType].New()
rescaler.SetInput(reader.GetOutput())
rescaler.SetOutputMinimum(0)
outputPixelTypeMaximum = itk.NumericTraits[OutputPixelType].max()
rescaler.SetOutputMaximum(outputPixelTypeMaximum)

castImageFilter = itk.CastImageFilter[InputImageType, OutputImageType].New()
castImageFilter.SetInput(rescaler.GetOutput())

writer = itk.ImageFileWriter[OutputImageType].New()
writer.SetFileName(outputImage)
writer.SetInput(castImageFilter.GetOutput())

writer.Update()
