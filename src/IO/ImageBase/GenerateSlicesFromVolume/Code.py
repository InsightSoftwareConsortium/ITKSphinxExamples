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

itk.auto_progress(2)

parser = argparse.ArgumentParser(description="Generate Slices From Volume.")
parser.add_argument("input_image")
parser.add_argument("output_image")
parser.add_argument("extension", nargs="?")
args = parser.parse_args()

if args.extension:
    extension = args.extension
else:
    extension = ".png"

fileNameFormat = args.output_image + "-%d" + extension

Dimension = 3

PixelType = itk.UC
InputImageType = itk.Image[PixelType, Dimension]

ReaderType = itk.ImageFileReader[InputImageType]
reader = ReaderType.New()
reader.SetFileName(args.input_image)

OutputPixelType = itk.UC
RescaleImageType = itk.Image[OutputPixelType, Dimension]

RescaleFilterType = itk.RescaleIntensityImageFilter[InputImageType, RescaleImageType]
rescale = RescaleFilterType.New()
rescale.SetInput(reader.GetOutput())
rescale.SetOutputMinimum(0)
rescale.SetOutputMaximum(255)
rescale.UpdateLargestPossibleRegion()

region = reader.GetOutput().GetLargestPossibleRegion()
size = region.GetSize()

fnames = itk.NumericSeriesFileNames.New()
fnames.SetStartIndex(0)
fnames.SetEndIndex(size[2] - 1)
fnames.SetIncrementIndex(1)
fnames.SetSeriesFormat(fileNameFormat)

OutputImageType = itk.Image[OutputPixelType, 2]

WriterType = itk.ImageSeriesWriter[RescaleImageType, OutputImageType]
writer = WriterType.New()
writer.SetInput(rescale.GetOutput())
writer.SetFileNames(fnames.GetFileNames())

writer.Update()
