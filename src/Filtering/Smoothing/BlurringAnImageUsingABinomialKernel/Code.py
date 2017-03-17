#!/usr/bin/env python

#==========================================================================
#
#   Copyright Insight Software Consortium
#
#   Licensed under the Apache License, Version 2.0 (the "License")
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

if len(sys.argv) != 4:
    print("Usage: " + sys.argv[0] + " <inputImage> <outputImage> <numberOfRepetitions>")
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]
numberOfRepetitions = int(sys.argv[3])

InputPixelType = itk.F
OutputPixelType = itk.UC
Dimension = 2

InputImageType = itk.Image[InputPixelType, Dimension]
OutputImageType = itk.Image[OutputPixelType, Dimension]

reader = itk.ImageFileReader[InputImageType].New()
reader.SetFileName(inputImage)

binomialFilter = itk.BinomialBlurImageFilter[InputImageType, InputImageType].New()
binomialFilter.SetInput(reader.GetOutput())
binomialFilter.SetRepetitions(numberOfRepetitions)

rescaler = itk.RescaleIntensityImageFilter[
    InputImageType,
    OutputImageType].New()
rescaler.SetInput(binomialFilter.GetOutput())
rescaler.SetOutputMinimum(0)
rescaler.SetOutputMaximum(255)

writer = itk.ImageFileWriter[OutputImageType].New()
writer.SetFileName(outputImage)
writer.SetInput(rescaler.GetOutput())

writer.Update()