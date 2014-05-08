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

if len(sys.argv) != 7:
    print("Usage: " + sys.argv[0] + " <inputImage> <outputImage>"
          "<OutputMin> <OutputMax> <Alpha> <Beta>")
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]

PixelType = itk.UC
Dimension = 2

ImageType = itk.Image[PixelType, Dimension]

outputMinimum = int(sys.argv[3])
outputMaximum = int(sys.argv[4])
alpha = float(sys.argv[5])
beta = float(sys.argv[6])

ReaderType = itk.ImageFileReader[ImageType]
reader = ReaderType.New()
reader.SetFileName(inputImage)

FilterType = itk.SigmoidImageFilter[ImageType, ImageType]
sigmoidFilter = FilterType.New()
sigmoidFilter.SetInput(reader.GetOutput())
sigmoidFilter.SetOutputMinimum(outputMinimum)
sigmoidFilter.SetOutputMaximum(outputMaximum)
sigmoidFilter.SetAlpha(alpha)
sigmoidFilter.SetBeta(beta)

WriterType = itk.ImageFileWriter[ImageType]
writer = WriterType.New()
writer.SetFileName(outputImage)
writer.SetInput(sigmoidFilter.GetOutput())

writer.Update()
