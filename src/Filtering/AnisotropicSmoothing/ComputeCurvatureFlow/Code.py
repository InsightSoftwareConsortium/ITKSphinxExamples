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

import itk
import argparse

parser = argparse.ArgumentParser(description="Compute Curvature Flow.")
parser.add_argument("input_image")
parser.add_argument("output_image")
parser.add_argument("number_of_iterations", type=int)
parser.add_argument("time_step", type=float)
args = parser.parse_args()

InputPixelType = itk.F
OutputPixelType = itk.UC
Dimension = 2

InputImageType = itk.Image[InputPixelType, Dimension]
OutputImageType = itk.Image[OutputPixelType, Dimension]

ReaderType = itk.ImageFileReader[InputImageType]
reader = ReaderType.New()
reader.SetFileName(args.input_image)

FilterType = itk.CurvatureFlowImageFilter[InputImageType, InputImageType]
curvatureFlowFilter = FilterType.New()

curvatureFlowFilter.SetInput(reader.GetOutput())
curvatureFlowFilter.SetNumberOfIterations(args.number_of_iterations)
curvatureFlowFilter.SetTimeStep(args.time_step)

RescaleFilterType = itk.RescaleIntensityImageFilter[InputImageType, OutputImageType]
rescaler = RescaleFilterType.New()
rescaler.SetInput(curvatureFlowFilter.GetOutput())

outputPixelTypeMinimum = itk.NumericTraits[OutputPixelType].min()
outputPixelTypeMaximum = itk.NumericTraits[OutputPixelType].max()

rescaler.SetOutputMinimum(outputPixelTypeMinimum)
rescaler.SetOutputMaximum(outputPixelTypeMaximum)

WriterType = itk.ImageFileWriter[OutputImageType]
writer = WriterType.New()
writer.SetFileName(args.output_image)
writer.SetInput(rescaler.GetOutput())

writer.Update()
