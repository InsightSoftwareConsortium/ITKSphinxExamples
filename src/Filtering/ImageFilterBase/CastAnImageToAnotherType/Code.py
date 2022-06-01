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

parser = argparse.ArgumentParser(description="Cast An Image To Another Type.")
parser.add_argument("input_image")
parser.add_argument("output_image")
args = parser.parse_args()

Dimension = 2
InputPixelType = itk.F
OutputPixelType = itk.UC

InputImageType = itk.Image[InputPixelType, Dimension]
OutputImageType = itk.Image[OutputPixelType, Dimension]

reader = itk.ImageFileReader[InputImageType].New()
reader.SetFileName(args.input_image)

rescaler = itk.RescaleIntensityImageFilter[InputImageType, InputImageType].New()
rescaler.SetInput(reader.GetOutput())
rescaler.SetOutputMinimum(0)
outputPixelTypeMaximum = itk.NumericTraits[OutputPixelType].max()
rescaler.SetOutputMaximum(outputPixelTypeMaximum)

castImageFilter = itk.CastImageFilter[InputImageType, OutputImageType].New()
castImageFilter.SetInput(rescaler.GetOutput())

writer = itk.ImageFileWriter[OutputImageType].New()
writer.SetFileName(args.output_image)
writer.SetInput(castImageFilter.GetOutput())

writer.Update()
