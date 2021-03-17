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

Dimension = 2

SizeType = itk.Size[Dimension]
size = SizeType()
size.Fill(3)

IndexType = itk.Index[Dimension]
start = IndexType()
start.Fill(0)

RegionType = itk.ImageRegion[Dimension]
region = RegionType(start, size)

testPixel1 = IndexType()
testPixel1[0] = 1
testPixel1[1] = 1

testPixel2 = IndexType()
testPixel2[0] = 6
testPixel2[1] = 6

print(testPixel1, end=" ")
if region.IsInside(testPixel1):
    print("Inside")
else:
    print("Outside")

print(testPixel2, end=" ")
if region.IsInside(testPixel2):
    print("Inside")
else:
    print("Outside")
