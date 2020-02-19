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

if len(sys.argv) != 5:
    print(
        "Usage: " + sys.argv[0] + " <inputImage> <outputImage> "
        "<numberOfIterations> <conductance>")
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]
numberOfIterations = int(sys.argv[3])
conductance = float(sys.argv[4])

Dimension = 2
InputPixelType = itk.UC
InputImageType = itk.Image[InputPixelType, Dimension]
OutputPixelType = itk.F
OutputImageType = itk.Image[OutputPixelType, Dimension]

ReaderType = itk.ImageFileReader[InputImageType]
reader = ReaderType.New()
reader.SetFileName(inputImage)

CastFilterType = itk.CastImageFilter[InputImageType, OutputImageType]
castfilter = CastFilterType.New()
castfilter.SetInput(reader)

FilterType = itk.GradientAnisotropicDiffusionImageFilter[
    OutputImageType, OutputImageType]
gradientfilter = FilterType.New()
gradientfilter.SetInput(castfilter.GetOutput())
gradientfilter.SetNumberOfIterations(numberOfIterations)
gradientfilter.SetTimeStep(0.125)
gradientfilter.SetConductanceParameter(conductance)

WriterType = itk.ImageFileWriter[OutputImageType]
writer = WriterType.New()
writer.SetFileName(outputImage)
writer.SetInput(gradientfilter.GetOutput())

writer.Update()
