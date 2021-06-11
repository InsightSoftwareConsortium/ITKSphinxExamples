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

parser = argparse.ArgumentParser(description="Erode A Binary Image.")
parser.add_argument("input_image")
parser.add_argument("output_image")
parser.add_argument("radius", type=int)
args = parser.parse_args()

PixelType = itk.UC
Dimension = 2

ImageType = itk.Image[PixelType, Dimension]

ReaderType = itk.ImageFileReader[ImageType]
reader = ReaderType.New()
reader.SetFileName(args.input_image)

StructuringElementType = itk.FlatStructuringElement[Dimension]
structuringElement = StructuringElementType.Ball(args.radius)

ErodeFilterType = itk.BinaryErodeImageFilter[
    ImageType, ImageType, StructuringElementType
]
erodeFilter = ErodeFilterType.New()
erodeFilter.SetInput(reader.GetOutput())
erodeFilter.SetKernel(structuringElement)
erodeFilter.SetForegroundValue(255)  # Intensity value to erode
erodeFilter.SetBackgroundValue(0)  # Replacement value for eroded voxels

WriterType = itk.ImageFileWriter[ImageType]
writer = WriterType.New()
writer.SetFileName(args.output_image)
writer.SetInput(erodeFilter.GetOutput())

writer.Update()
