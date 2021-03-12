#!/usr/bin/env python

# ==========================================================================
#
#   Copyright NumFOCUS
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
from numpy.core import double

Dimension = 3
CoordType = itk.D

VectorType = itk.Vector[CoordType, Dimension]

u = VectorType()
u[0] = -1.0
u[1] = 1.0
u[2] = -1.0

v = VectorType()
v[0] = 1.0
v[1] = 2.0
v[2] = 3.0

print("u: " + str(u))
print("v: " + str(v))
print("DotProduct( u, v ) = " + str(u * v))
print("DotProduct( u, v ) = " + str(u - double(u * v) * v))
