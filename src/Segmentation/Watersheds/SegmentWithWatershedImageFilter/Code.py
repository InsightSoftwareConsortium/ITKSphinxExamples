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

# Run with:
# ./WatershedImageFilter.py <InputFileName> <OutputFileName> <Threshold> <Level>
# e.g.
# ./WatershedImageFilter.py BrainProtonDensitySlice.png OutBrainWatershed.png 0.005 .5
# (A rule of thumb is to set the Threshold to be about 1 / 100 of the Level.)
#
#  threshold: absolute minimum height value used during processing.
#        Raising this threshold percentage effectively decreases the number of local minima in the input, 
#        resulting in an initial segmentation with fewer regions. 
#        The assumption is that the shallow regions that thresholding removes are of of less interest.
#  level: parameter controls the depth of metaphorical flooding of the image. 
#        That is, it sets the maximum saliency value of interest in the result. 
#        Raising and lowering the Level influences the number of segments 
#        in the basic segmentation that are merged to produce the final output. 
#        A level of 1.0 is analogous to flooding the image up to a 
#        depth that is 100 percent of the maximum value in the image. 
#        A level of 0.0 produces the basic segmentation, which will typically be very oversegmented. 
#        Level values of interest are typically low (i.e. less than about 0.40 or 40%),
#        since higher values quickly start to undersegment the image.

import sys
import itk

if len(sys.argv) != 5:
    print('Usage: ' + sys.argv[0] +
          ' <InputFileName> <OutputFileName> <Threshold> <Level>')
    sys.exit(1)

inputFileName = sys.argv[1]
outputFileName = sys.argv[2]

Dimension = 2

FloatPixelType = itk.ctype('float')
FloatImageType = itk.Image[FloatPixelType, Dimension]

reader = itk.ImageFileReader[FloatImageType].New()
reader.SetFileName(inputFileName)

gradientMagnitude = \
    itk.GradientMagnitudeImageFilter.New(Input=reader.GetOutput())

watershed = \
    itk.WatershedImageFilter.New(Input=gradientMagnitude.GetOutput())

threshold = float(sys.argv[3])
level = float(sys.argv[4])
watershed.SetThreshold(threshold)
watershed.SetLevel(level)

LabeledImageType = type(watershed.GetOutput())

PixelType = itk.ctype('unsigned char')
RGBPixelType = itk.RGBPixel[PixelType]
RGBImageType = itk.Image[RGBPixelType, Dimension]

ScalarToRGBColormapFilterType = \
    itk.ScalarToRGBColormapImageFilter[LabeledImageType, RGBImageType]
colormapImageFilter = ScalarToRGBColormapFilterType.New()
colormapImageFilter.SetColormap(ScalarToRGBColormapFilterType.Jet)
colormapImageFilter.SetInput(watershed.GetOutput())
colormapImageFilter.Update()

WriterType = itk.ImageFileWriter[RGBImageType]
writer = WriterType.New()
writer.SetFileName(outputFileName)
writer.SetInput(colormapImageFilter.GetOutput())
writer.Update()
