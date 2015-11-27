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

import sys
import itk

from distutils.version import StrictVersion as VS
if VS(itk.Version.GetITKVersion()) < VS("4.9.0"):
    print("ITK 4.9.0 is required.")
    sys.exit(1)

Dimension = 2

index = itk.Index[Dimension]()
index.Fill(5)

offset = itk.Offset[Dimension]()
offset.Fill(1)

newIndex = index + offset

print("index: " + str([int(index[0]), int(index[1])]))
print("offset: " + str([int(offset[0]), int(offset[1])]))
print("index + offset: " + str([int(newIndex[0]), int(newIndex[1])]))
print("")

offset[0] = -1
newIndex = index + offset

print("index: " + str([int(index[0]), int(index[1])]))
print("offset: " + str([int(offset[0]), int(offset[1])]))
print("index + offset: " + str([int(newIndex[0]), int(newIndex[1])]))
print("")
