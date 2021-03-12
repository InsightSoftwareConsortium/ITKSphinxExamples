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

if len(sys.argv) != 3:
    print("Usage: " + sys.argv[0] + " <InputFileName> <OutputFileName>")
    sys.exit(1)

VectorDimension = 4

PixelType = itk.Vector[itk.F, VectorDimension]

ImageDimension = 3

ImageType = itk.Image[PixelType, ImageDimension]

reader = itk.ImageFileReader[ImageType].New()
reader.SetFileName(sys.argv[1])

writer = itk.ImageFileWriter[ImageType].New()
writer.SetFileName(sys.argv[2])
writer.SetInput(reader.GetOutput())
writer.Update()
