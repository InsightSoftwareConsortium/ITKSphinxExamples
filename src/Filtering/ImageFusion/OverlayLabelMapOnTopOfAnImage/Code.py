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

import sys
import itk
import argparse

parser = argparse.ArgumentParser(description="Overlay Label Map On Top Of An Image.")
parser.add_argument("input_image")
parser.add_argument("label_map")
parser.add_argument("output_image")
args = parser.parse_args()

PixelType = itk.ctype("unsigned char")
Dimension = 2

ImageType = itk.Image[PixelType, Dimension]


reader = itk.ImageFileReader[ImageType].New()
reader.SetFileName(args.input_image)

labelReader = itk.ImageFileReader[ImageType].New()
labelReader.SetFileName(args.label_map)


LabelType = itk.ctype("unsigned long")
LabelObjectType = itk.StatisticsLabelObject[LabelType, Dimension]
LabelMapType = itk.LabelMap[LabelObjectType]

converter = itk.LabelImageToLabelMapFilter[ImageType, LabelMapType].New()
converter.SetInput(labelReader)

RGBImageType = itk.Image[itk.RGBPixel[PixelType], Dimension]
overlayFilter = itk.LabelMapOverlayImageFilter[
    LabelMapType, ImageType, RGBImageType
].New()
overlayFilter.SetInput(converter.GetOutput())
overlayFilter.SetFeatureImage(reader.GetOutput())
overlayFilter.SetOpacity(0.5)


itk.imwrite(overlayFilter.GetOutput(), args.output_image)
