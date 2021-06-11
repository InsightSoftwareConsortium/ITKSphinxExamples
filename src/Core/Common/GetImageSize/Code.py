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

import numpy as np
import itk
import argparse

parser = argparse.ArgumentParser(description="Get Image Size.")
parser.add_argument("input_image")
args = parser.parse_args()

image = itk.imread(args.input_image, itk.UC)

region = image.GetLargestPossibleRegion()
size = region.GetSize()

print(size)

# Equivalently
size = itk.size(image)

print(size)

# Corresponds to the NumPy ndarray shape. Note that the ordering is reversed.
print(np.asarray(image).shape)

# An example image had w = 200 and h = 100
# (it is wider than it is tall). The above output
# 200 x 100
# so w = GetSize()[0]
# and h = GetSize()[1]

# A pixel inside the region
indexInside = itk.Index[2]()
indexInside[0] = 150
indexInside[1] = 50
print(region.IsInside(indexInside))

# A pixel outside the region
indexOutside = itk.Index[2]()
indexOutside[0] = 50
indexOutside[1] = 150
print(region.IsInside(indexOutside))

# This means that the [0] component of the index is referencing the
# left to right (x) value and the [1] component of Index is referencing
# the top to bottom (y) value
