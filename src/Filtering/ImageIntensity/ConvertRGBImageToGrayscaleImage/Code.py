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

if len(sys.argv) != 3:
    print("Usage: " + sys.argv[0] + " <InputFileName> <OutputFileName>")
    sys.exit(1)

inputFileName = sys.argv[1]
outputFileName = sys.argv[2]

Dimension = 2

ComponentType = itk.UC
InputPixelType = itk.RGBPixel[ComponentType]
InputImageType = itk.Image[InputPixelType, Dimension]

OutputPixelType = itk.UC
OutputImageType = itk.Image[OutputPixelType, Dimension]

reader = itk.ImageFileReader[InputImageType].New()
reader.SetFileName(inputFileName)

rgbFilter = itk.RGBToLuminanceImageFilter.New(reader)

writer = itk.ImageFileWriter[OutputImageType].New()
writer.SetFileName(outputFileName)
writer.SetInput(rgbFilter.GetOutput())

writer.Update()
