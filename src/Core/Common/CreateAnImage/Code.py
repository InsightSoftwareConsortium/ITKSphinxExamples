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
PixelType = itk.ctype('unsigned char')
ImageType = itk.Image[PixelType, Dimension]

image = ImageType.New()

start = itk.Index[Dimension]()
start[0] = 0  # first index on X
start[1] = 0  # first index on Y
start[2] = 0  # first index on Z

size = itk.Size[Dimension]()
size[0] = 200  # size along X
size[1] = 200  # size along Y
size[2] = 200  # size along Z

region = itk.ImageRegion[Dimension]()
region.SetSize(size)
region.SetIndex(start)

image.SetRegions(region)
image.Allocate()

print(image)
