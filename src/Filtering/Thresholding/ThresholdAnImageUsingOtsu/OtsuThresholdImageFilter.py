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

if len(sys.argv) < 6:
    print("Usage: " + sys.argv[0] + " <inputImage> <outputImage> "
          "<numberOfHistogramBins> <numberOfThresholds> <labelOffset>")
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]
numberOfHistogramBins = int(sys.argv[3])
numberOfThresholds = int(sys.argv[4])
labelOffset = int(sys.argv[5])

PixelType = itk.UC
Dimension = 2

ImageType = itk.Image[PixelType, Dimension]

ReaderType = itk.ImageFileReader[ImageType]
reader = ReaderType.New()
reader.SetFileName(inputImage)

FilterType = itk.OtsuMultipleThresholdsImageFilter[ImageType, ImageType]
thresholdFilter = FilterType.New()

thresholdFilter.SetInput(reader.GetOutput())

thresholdFilter.SetNumberOfHistogramBins(numberOfHistogramBins)
thresholdFilter.SetNumberOfThresholds(numberOfThresholds)
thresholdFilter.SetLabelOffset(labelOffset)

RescaleFilterType = itk.RescaleIntensityImageFilter[ImageType, ImageType]
rescaler = RescaleFilterType.New()
rescaler.SetInput( thresholdFilter.GetOutput() )
rescaler.SetOutputMinimum( 0 )
rescaler.SetOutputMaximum( 255 )

WriterType = itk.ImageFileWriter[ImageType]
writer = WriterType.New()
writer.SetFileName(outputImage)
writer.SetInput(rescaler.GetOutput())

writer.Update()
