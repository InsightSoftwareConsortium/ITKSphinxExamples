#!/usr/bin/env python

#==========================================================================
#
#   Copyright Insight Software Consortium
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================*/

import sys
import itk

if len(sys.argv) != 3:
    print("Usage: " + sys.argv[0] + " <input1> <input2> <input3> ... <output>")
    sys.exit(1)

InputDimension = 2
OutputDimension = 3

PixelType = itk.UC

InputImageType = itk.Image[PixelType, InputDimension]
OutputImageType = itk.Image[PixelType, OutputDimension]

reader = itk.ImageFileReader[InputImageType].New()

tileFilter = itk.TileImageFilter[InputImageType, OutputImageType].New()

layout = [2, 2, 0]
tileFilter.SetLayout(layout)

for ii in range(1, len(sys.argv)-1):
    reader.SetFileName(sys.argv[ii])
    reader.Update()

    inputImage = reader.GetOutput()
    inputImage.DisconnectPipeline()

    tileFilter.SetInput(ii-1, inputImage)

defaultValue = 128
tileFilter.SetDefaultPixelValue(defaultValue)
tileFilter.Update()

writer = itk.ImageFileWriter[OutputImageType].New()
writer.SetFileName(sys.argv[-1])
writer.SetInput(tileFilter.GetOutput())
writer.Update()
