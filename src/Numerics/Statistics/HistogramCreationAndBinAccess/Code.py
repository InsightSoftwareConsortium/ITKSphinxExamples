#!/usr/bin/env python

#==========================================================================
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
#==========================================================================*/

from __future__ import print_function

import itk

numberOfComponents = 2

histogram = itk.Histogram.New(MeasurementVectorSize = numberOfComponents)

# We initialize it as a 3x3 histogram with equal size intervals.

size = itk.Size[numberOfComponents]()
size.Fill(3)

lowerBound = 1.1, 2.6
upperBound = 7.1, 8.6
histogram.Initialize(size, lowerBound, upperBound)

# Now the histogram is ready for storing frequency values. There
# are three ways of accessing data elements in the histogram:
# - using instance identifiers---just like any other Sample object;
# - using n-dimensional indices---just like an Image object;
# - using an iterator---just like any other Sample object.
#
# In this example, the index (0, 0) refers the same bin as the instance
# identifier (0) refers to. The instance identifier of the index (0,
# 1) is (3), (0, 2) is (6), (2, 2) is (8), and so on.

frequencies = [
    (0, 0),
    (1, 2),
    (2, 3),
    (3, 2),
    (4, 1),
    (5, 1),
    (6, 5),
    (7, 4),
    (8, 0)
]

for instance_identifier, frequency in frequencies:
    histogram.SetFrequency(instance_identifier, frequency)

# Let us examine if the frequency is set correctly by calling the
# GetFrequency(index) method. We can use the
# GetFrequency(instance identifier) method for the same purpose.

index = [0, 2]
print("Frequency of the bin at index", index,
      "is", histogram.GetFrequency(index),
      "and the bin's instance identifier is",
      histogram.GetInstanceIdentifier(index))
