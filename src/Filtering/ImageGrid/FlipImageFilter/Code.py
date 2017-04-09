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

if len(sys.argv) != 5:
    print('Usage: ' + sys.argv[0] + ' <InputFileName> <OutputFileName> <FlipAxisX> <FlipAxisY>')
    sys.exit(1)

inputFileName = sys.argv[1]
outputFileName = sys.argv[2]

Dimension = 2
PixelType = itk.UC
ImageType = itk.Image[PixelType, Dimension]

reader = itk.ImageFileReader[ImageType].New()
reader.SetFileName(inputFileName)
writer = itk.ImageFileWriter[ImageType].New()
writer.SetFileName(outputFileName)

FlipImageType = itk.FlipImageFilter[ImageType].New()
FlipAxesArray = itk.Index[Dimension]()
FlipAxesArray[0] = int(sys.argv[3])
FlipAxesArray[1] = int(sys.argv[4])

FlipImageType.SetFlipAxes(FlipAxesArray)
FlipImageType.SetInput(reader.GetOutput())
writer.SetInput(FlipImageType.GetOutput())
writer.Update()
