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

derivativeOperator = itk.DerivativeOperator[itk.F, 2]()
derivativeOperator.SetDirection(0)  # Create the operator for the X axis derivative
radius = itk.Size[2]()
radius.Fill(1)
derivativeOperator.CreateToRadius(radius)

print("Size: " + str(derivativeOperator.GetSize()))

print(derivativeOperator)

for i in range(9):
    print(str(derivativeOperator.GetOffset(i)) + " " + str(derivativeOperator.GetElement(i)))
