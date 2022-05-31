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

MyType = itk.F

print("Min: " + str(itk.NumericTraits[MyType].min()))
print("Max: " + str(itk.NumericTraits[MyType].max()))
print("ZeroValue: " + str(itk.NumericTraits[MyType].ZeroValue()))

print("Is -1 negative? " + str(itk.NumericTraits[MyType].IsNegative(-1)))

print("Is 1 negative? " + str(itk.NumericTraits[MyType].IsNegative(1)))

print("OneValue: " + str(itk.NumericTraits[MyType].OneValue()))

print("Epsilon: " + str(itk.NumericTraits[MyType].epsilon()))

print("Infinity: " + str(itk.NumericTraits[MyType].infinity()))

if 0 == itk.NumericTraits[MyType].infinity():
    print(" 0 == inf!")
    exit(1)
else:
    print("Good")
    exit(0)
