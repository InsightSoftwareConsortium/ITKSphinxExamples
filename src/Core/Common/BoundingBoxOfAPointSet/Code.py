#!/usr/bin/env python

# Copyright NumFOCUS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#        https://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import itk
import platform

Dimension = 3
CoordType = itk.ctype("float")
# Windows requires unsigned long long for 64-bit identifiers
if platform.system() == "Windows":
    ElementIdentifierType = itk.ctype("unsigned long long")
else:
    ElementIdentifierType = itk.ctype("unsigned long")


PointSetType = itk.PointSet[CoordType, Dimension]

pointSet = PointSetType.New()
points = pointSet.GetPoints()

# Create points
p0 = itk.Point[CoordType, Dimension]()
p1 = itk.Point[CoordType, Dimension]()
p2 = itk.Point[CoordType, Dimension]()

p0[0] = 0.0
p0[1] = 0.0
p0[2] = 0.0
p1[0] = 0.1
p1[1] = 0.0
p1[2] = 0.0
p2[0] = 0.0
p2[1] = 0.1
p2[2] = 0.0

points.InsertElement(0, p0)
points.InsertElement(1, p1)
points.InsertElement(2, p2)

VecContType = itk.VectorContainer[
    ElementIdentifierType, itk.Point[CoordType, Dimension]
]
BoundingBoxType = itk.BoundingBox[
    ElementIdentifierType, Dimension, CoordType, VecContType
]

boundingBox = BoundingBoxType.New()
boundingBox.SetPoints(points)
boundingBox.ComputeBoundingBox()

print("bounds: " + str(boundingBox.GetBounds()))
print("center: " + str(boundingBox.GetCenter()))
print("diagonal length squared: " + str(boundingBox.GetDiagonalLength2()))
