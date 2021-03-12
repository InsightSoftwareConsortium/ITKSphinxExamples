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

if len(sys.argv) != 5:
    print(
        "Usage: " + sys.argv[0] + " <inputImage> <outputImage> "
        "<lowerThreshold> <upperThreshold>"
    )
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]
lowerThreshold = int(sys.argv[3])
upperThreshold = int(sys.argv[4])

PixelType = itk.UC
Dimension = 2

ImageType = itk.Image[PixelType, Dimension]

reader = itk.ImageFileReader[ImageType].New()
reader.SetFileName(inputImage)

thresholdFilter = itk.ThresholdImageFilter[ImageType].New()

thresholdFilter.SetInput(reader.GetOutput())
thresholdFilter.ThresholdOutside(lowerThreshold, upperThreshold)
thresholdFilter.SetOutsideValue(0)

writer = itk.ImageFileWriter[ImageType].New()
writer.SetFileName(outputImage)
writer.SetInput(thresholdFilter.GetOutput())

writer.Update()
