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

parser = argparse.ArgumentParser(description="Compute Sigmoid.")
parser.add_argument("input_image")
parser.add_argument("output_image")
parser.add_argument("output_min", type=int)
parser.add_argument("output_max", type=int)
parser.add_argument("alpha", type=float)
parser.add_argument("beta", type=float)
args = parser.parse_args()

PixelType = itk.UC
Dimension = 2

ImageType = itk.Image[PixelType, Dimension]

reader = itk.ImageFileReader[ImageType].New()
reader.SetFileName(args.input_image)

sigmoidFilter = itk.SigmoidImageFilter[ImageType, ImageType].New()
sigmoidFilter.SetInput(reader.GetOutput())
sigmoidFilter.SetOutputMinimum(args.output_min)
sigmoidFilter.SetOutputMaximum(args.output_max)
sigmoidFilter.SetAlpha(args.alpha)
sigmoidFilter.SetBeta(args.beta)

writer = itk.ImageFileWriter[ImageType].New()
writer.SetFileName(args.output_image)
writer.SetInput(sigmoidFilter.GetOutput())

writer.Update()
