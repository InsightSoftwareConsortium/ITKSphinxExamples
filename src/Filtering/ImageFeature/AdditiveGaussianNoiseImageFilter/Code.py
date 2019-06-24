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
    print("Usage: " + sys.argv[0] + "< Input Image > < Output Image > [Mean] [Standard Deviation]")
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]
mean = float(sys.argv[3])
deviation = float(sys.argv[4])

# Use unsigned char to save to PNG format
InputPixelType = itk.UC
OutputPixelType = itk.UC
Dimension = 2

InputImageType = itk.Image[InputPixelType, Dimension]
OutputImageType = itk.Image[OutputPixelType, Dimension]

ReaderType = itk.ImageFileReader[InputImageType]
reader = ReaderType.New()
reader.SetFileName(inputImage)

FilterType = itk.AdditiveGaussianNoiseImageFilter[InputImageType, InputImageType]
AdditiveFilter = FilterType.New()
AdditiveFilter.SetInput(reader.GetOutput())
AdditiveFilter.SetMean(mean)
AdditiveFilter.SetStandardDeviation(deviation)

WriterType = itk.ImageFileWriter[OutputImageType]
writer = WriterType.New()
writer.SetFileName(outputImage)
writer.SetInput(AdditiveFilter.GetOutput())

writer.Update()
