#!/usr/bin/env python

# Copyright Insight Software Consortium
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

if len(sys.argv) != 6:
    print("Usage: " + sys.argv[0] + " <inputImage> <outputImage> "
          "<numberOfIterations> <timeStep> <conductance>")
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]
numberOfIterations = int(sys.argv[3])
timeStep = float(sys.argv[4])
conductance = float(sys.argv[5])

InputPixelType = itk.F
OutputPixelType = itk.UC
Dimension = 2

InputImageType = itk.Image[InputPixelType, Dimension]
OutputImageType = itk.Image[OutputPixelType, Dimension]

ReaderType = itk.ImageFileReader[InputImageType]
reader = ReaderType.New()
reader.SetFileName(inputImage)

FilterType = itk.CurvatureAnisotropicDiffusionImageFilter[
    InputImageType, InputImageType]
curvatureAnisotropicDiffusionFilter = FilterType.New()

curvatureAnisotropicDiffusionFilter.SetInput(reader.GetOutput())
curvatureAnisotropicDiffusionFilter.SetNumberOfIterations(numberOfIterations)
curvatureAnisotropicDiffusionFilter.SetTimeStep(timeStep)
curvatureAnisotropicDiffusionFilter.SetConductanceParameter(conductance)

RescaleFilterType = itk.RescaleIntensityImageFilter[
    InputImageType, OutputImageType]
rescaler = RescaleFilterType.New()
rescaler.SetInput(curvatureAnisotropicDiffusionFilter.GetOutput())

outputPixelTypeMinimum = itk.NumericTraits[OutputPixelType].min()
outputPixelTypeMaximum = itk.NumericTraits[OutputPixelType].max()

rescaler.SetOutputMinimum(outputPixelTypeMinimum)
rescaler.SetOutputMaximum(outputPixelTypeMaximum)

WriterType = itk.ImageFileWriter[OutputImageType]
writer = WriterType.New()
writer.SetFileName(outputImage)
writer.SetInput(rescaler.GetOutput())

writer.Update()
