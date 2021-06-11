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

import itk
import argparse

parser = argparse.ArgumentParser(description="Read Write Vector Image.")
parser.add_argument("input_image")
parser.add_argument("output_image")
args = parser.parse_args()

VectorDimension = 4

PixelType = itk.Vector[itk.F, VectorDimension]

ImageDimension = 3

ImageType = itk.Image[PixelType, ImageDimension]

reader = itk.ImageFileReader[ImageType].New()
reader.SetFileName(args.input_image)

writer = itk.ImageFileWriter[ImageType].New()
writer.SetFileName(args.output_image)
writer.SetInput(reader.GetOutput())
writer.Update()
