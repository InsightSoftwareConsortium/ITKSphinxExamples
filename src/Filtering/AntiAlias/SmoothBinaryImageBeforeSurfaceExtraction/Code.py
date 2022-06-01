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
    description="Smooth Binary Image Before Surface Extraction."
)
parser.add_argument("input_image")
parser.add_argument("output_image")
parser.add_argument("maximum_RMS_error", type=float)
parser.add_argument("number_of_iterations", type=int)
parser.add_argument("number_of_layers", type=int)
args = parser.parse_args()

PixelType = itk.F
Dimension = 2
ImageType = itk.Image[PixelType, Dimension]

ReaderType = itk.ImageFileReader[ImageType]
reader = ReaderType.New()
reader.SetFileName(args.input_image)

AntiAliasFilterType = itk.AntiAliasBinaryImageFilter[ImageType, ImageType]
antialiasfilter = AntiAliasFilterType.New()
antialiasfilter.SetInput(reader.GetOutput())
antialiasfilter.SetMaximumRMSError(args.maximum_RMS_error)
antialiasfilter.SetNumberOfIterations(args.number_of_iterations)
antialiasfilter.SetNumberOfLayers(args.number_of_layers)

WriterType = itk.ImageFileWriter[ImageType]
writer = WriterType.New()
writer.SetFileName(args.output_image)
writer.SetInput(antialiasfilter.GetOutput())

writer.Update()
