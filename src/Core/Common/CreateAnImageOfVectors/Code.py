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

import itk

Dimension = 3
ComponentType = itk.ctype('float')
PixelType = itk.Vector[ComponentType, Dimension]
ImageType = itk.Image[PixelType, Dimension]

image = ImageType.New()

start = itk.Index[Dimension]()
start[0] = 0
start[1] = 0
start[2] = 0

size = itk.Size[Dimension]()
size[0] = 200
size[1] = 200
size[2] = 200

region = itk.ImageRegion[Dimension]()
region.SetSize(size)
region.SetIndex(start)

image.SetRegions(region)
image.Allocate()

vectorValue = PixelType()
vectorValue[0] = 0
vectorValue[1] = 0
vectorValue[2] = 0
image.FillBuffer(vectorValue)

pixelIndex = itk.Index[Dimension]()
pixelIndex[0] = 27
pixelIndex[1] = 29
pixelIndex[2] = 37

pixelValue = PixelType()
pixelValue[0] = 1.345
pixelValue[1] = 6.841
pixelValue[2] = 3.295

image.SetPixel(pixelIndex, pixelValue)

value = image.GetPixel(pixelIndex)

print(value)
