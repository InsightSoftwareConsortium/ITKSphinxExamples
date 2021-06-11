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

parser = argparse.ArgumentParser(description="Apply A Colormap To An Image.")
parser.add_argument("input_image")
parser.add_argument("output_image")
args = parser.parse_args()
PixelType = itk.UC
Dimension = 2

ImageType = itk.Image[PixelType, Dimension]

ReaderType = itk.ImageFileReader[ImageType]
reader = ReaderType.New()
reader.SetFileName(args.input_image)

RGBPixelType = itk.RGBPixel[PixelType]
RGBImageType = itk.Image[RGBPixelType, Dimension]

RGBFilterType = itk.ScalarToRGBColormapImageFilter[ImageType, RGBImageType]
rgbfilter = RGBFilterType.New()
rgbfilter.SetInput(reader.GetOutput())
rgbfilter.SetColormap(itk.ScalarToRGBColormapImageFilterEnums.RGBColormapFilter_Hot)

WriterType = itk.ImageFileWriter[RGBImageType]
writer = WriterType.New()
writer.SetFileName(args.output_image)
writer.SetInput(rgbfilter.GetOutput())

writer.Update()
