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

parser = argparse.ArgumentParser(description="Additive Gaussian Noise Image Filter.")
parser.add_argument("input_image")
parser.add_argument("output_image")
parser.add_argument("mean", type=float)
parser.add_argument("standard_deviation", type=float)
args = parser.parse_args()

# Use unsigned char to save to PNG format
InputPixelType = itk.UC
OutputPixelType = itk.UC
Dimension = 2

InputImageType = itk.Image[InputPixelType, Dimension]
OutputImageType = itk.Image[OutputPixelType, Dimension]

ReaderType = itk.ImageFileReader[InputImageType]
reader = ReaderType.New()
reader.SetFileName(args.input_image)

FilterType = itk.AdditiveGaussianNoiseImageFilter[InputImageType, InputImageType]
AdditiveFilter = FilterType.New()
AdditiveFilter.SetInput(reader.GetOutput())
AdditiveFilter.SetMean(args.mean)
AdditiveFilter.SetStandardDeviation(args.standard_deviation)

WriterType = itk.ImageFileWriter[OutputImageType]
writer = WriterType.New()
writer.SetFileName(args.output_image)
writer.SetInput(AdditiveFilter.GetOutput())

writer.Update()
