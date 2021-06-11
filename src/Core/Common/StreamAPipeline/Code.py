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
import argparse

from distutils.version import StrictVersion as VS

if VS(itk.Version.GetITKVersion()) < VS("4.10.0"):
    print("ITK 4.10.0 is required.")
    sys.exit(1)

parser = argparse.ArgumentParser(description="Stream A Pipeline.")
parser.add_argument("number_of_splits", type=int)
args = parser.parse_args()

Dimension = 2
PixelType = itk.UC
ImageType = itk.Image[PixelType, Dimension]

source = itk.RandomImageSource[ImageType].New()
size = itk.Size[Dimension]()
size.Fill(args.number_of_splits)
source.SetSize(size)

monitorFilter = itk.PipelineMonitorImageFilter[ImageType].New()
monitorFilter.SetInput(source.GetOutput())

streamingFilter = itk.StreamingImageFilter[ImageType, ImageType].New()
streamingFilter.SetInput(monitorFilter.GetOutput())
streamingFilter.SetNumberOfStreamDivisions(args.number_of_splits)

streamingFilter.Update()

print(
    "The output LargestPossibleRegion is: "
    + str(streamingFilter.GetOutput().GetLargestPossibleRegion())
)

print("")

updatedRequestedRegions = monitorFilter.GetUpdatedRequestedRegions()
print("Updated ApplyAFilterOnlyToASpecifiedImageRegion's:")
for ii in range(len(updatedRequestedRegions)):
    print("  " + str(updatedRequestedRegions[ii]))
