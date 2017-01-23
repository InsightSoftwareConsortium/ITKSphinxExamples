#!/usr/bin/env python

# ==========================================================================
#
#   Copyright Insight Software Consortium
#
#   Licensed under the Apache License, Version 2.0 (the "License")
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
# ==========================================================================*/

import itk

PixelType = itk.F
Dimension = 3

MeshTraits = itk.DefaultStaticMeshTraits[PixelType, Dimension, Dimension]
PointSetType = itk.PointSet[PixelType, Dimension, MeshTraits]
PointSet = PointSetType.New()

points = PointSet.GetPoints()

# Create points
p0 = itk.Point[PixelType, Dimension]()
p1 = itk.Point[PixelType, Dimension]()
p2 = itk.Point[PixelType, Dimension]()

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
