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

parser = argparse.ArgumentParser(
    description="Detect Edges With Canny Edge Detection Filter."
)
parser.add_argument("input_image")
parser.add_argument("output_image")
parser.add_argument("variance", type=float)
parser.add_argument("lower_threshold", type=float)
parser.add_argument("upper_threshold", type=float)
args = parser.parse_args()

InputPixelType = itk.F
OutputPixelType = itk.UC
Dimension = 2

InputImageType = itk.Image[InputPixelType, Dimension]
OutputImageType = itk.Image[OutputPixelType, Dimension]

reader = itk.ImageFileReader[InputImageType].New()
reader.SetFileName(args.input_image)

cannyFilter = itk.CannyEdgeDetectionImageFilter[InputImageType, InputImageType].New()
cannyFilter.SetInput(reader.GetOutput())
cannyFilter.SetVariance(args.variance)
cannyFilter.SetLowerThreshold(args.lower_threshold)
cannyFilter.SetUpperThreshold(args.upper_threshold)

rescaler = itk.RescaleIntensityImageFilter[InputImageType, OutputImageType].New()
rescaler.SetInput(cannyFilter.GetOutput())
rescaler.SetOutputMinimum(0)
rescaler.SetOutputMaximum(255)

writer = itk.ImageFileWriter[OutputImageType].New()
writer.SetFileName(args.output_image)
writer.SetInput(rescaler.GetOutput())

writer.Update()
