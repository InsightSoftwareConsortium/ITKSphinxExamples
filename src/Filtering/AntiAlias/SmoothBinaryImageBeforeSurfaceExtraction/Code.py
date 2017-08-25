#!/usr/bin/env python

# Copyright Insight Software Consortium
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

if len(sys.argv) != 6:
    print("Usage: " + sys.argv[0] + " <inputImage> <outputImage> "
          "<maximumRMSError> <numberOfIterations> <numberOfLayers>")
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]
maximumRMSError = float(sys.argv[3])
numberOfIterations = int(sys.argv[4])
numberOfLayers = int(sys.argv[5])

PixelType = itk.F
Dimension = 2
ImageType = itk.Image[PixelType, Dimension]

ReaderType = itk.ImageFileReader[ImageType]
reader = ReaderType.New()
reader.SetFileName(inputImage)

AntiAliasFilterType = itk.AntiAliasBinaryImageFilter[ImageType, ImageType]
antialiasfilter = AntiAliasFilterType.New()
antialiasfilter.SetInput(reader.GetOutput())
antialiasfilter.SetMaximumRMSError(maximumRMSError)
antialiasfilter.SetNumberOfIterations(numberOfIterations)
antialiasfilter.SetNumberOfLayers(numberOfLayers)

WriterType = itk.ImageFileWriter[ImageType]
writer = WriterType.New()
writer.SetFileName(outputImage)
writer.SetInput(antialiasfilter.GetOutput())

writer.Update()
