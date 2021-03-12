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

itk.auto_progress(2)

if len(sys.argv) < 3:
    print("Usage: " + sys.argv[0] + " <InputFileName> <OutputFileName>")
    sys.exit(1)

inputFileName = sys.argv[1]
outputFileName = sys.argv[2]

xDiv = 6
yDiv = 4
zDiv = 1
# 1 for 2D input

Dimension = 3

PixelType = itk.UC
ImageType = itk.Image[PixelType, Dimension]

ReaderType = itk.ImageFileReader[ImageType]
reader = ReaderType.New()
reader.SetFileName(inputFileName)
reader.UpdateOutputInformation()
fullRegion = reader.GetOutput().GetLargestPossibleRegion()
fullSize = fullRegion.GetSize()
# when reading image from file, start index is always 0

# create variables of the proper types
start = itk.Index[Dimension]()
end = itk.Index[Dimension]()
size = itk.Size[Dimension]()

MedianType = itk.MedianImageFilter[ImageType, ImageType]
median = MedianType.New()
median.SetInput(reader.GetOutput())
median.SetRadius(2)

WriterType = itk.ImageFileWriter[ImageType]
writer = WriterType.New()
writer.SetFileName(outputFileName)

# Use for loops to split the image into chunks.
# This way of splitting gives us easy control over it.
# For example, we could make the regions always be of equal size
# in order to create samples for a deep learning algorithm.
# ImageRegionSplitterMultidimensional has a similar
# functionality to what is implemented below.
for z in range(zDiv):
    start[2] = int(fullSize[2] * float(z) / zDiv)
    end[2] = int(fullSize[2] * (z + 1.0) / zDiv)
    size[2] = end[2] - start[2]

    for y in range(yDiv):
        start[1] = int(fullSize[1] * float(y) / yDiv)
        end[1] = int(fullSize[1] * (y + 1.0) / yDiv)
        size[1] = end[1] - start[1]

        for x in range(xDiv):
            start[0] = int(fullSize[0] * float(x) / xDiv)
            end[0] = int(fullSize[0] * (x + 1.0) / xDiv)
            size[0] = end[0] - start[0]

            region = itk.ImageRegion[Dimension]()
            region.SetIndex(start)
            region.SetSize(size)

            # now that we have our chunk, request the filter to only process that
            median.GetOutput().SetRequestedRegion(region)
            median.Update()
            result = median.GetOutput()

            # only needed in case of further manual processing
            result.DisconnectPipeline()

            # possible additional non-ITK pipeline processing

            writer.SetInput(result)

            # convert region into IO region
            ioRegion = itk.ImageIORegion(Dimension)
            ioRegion.SetIndex(0, start[0])
            ioRegion.SetIndex(1, start[1])
            ioRegion.SetIndex(2, start[2])
            ioRegion.SetSize(0, region.GetSize()[0])
            ioRegion.SetSize(1, region.GetSize()[1])
            ioRegion.SetSize(2, region.GetSize()[2])
            # tell the writer this is only a chunk of a larger image
            writer.SetIORegion(ioRegion)

            try:
                writer.Update()
            except Exception as e:
                print("Exception for chunk:", x, y, z, "\n", e)
                sys.exit(1)
