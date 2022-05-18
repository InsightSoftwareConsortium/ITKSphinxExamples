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

import sys
import itk
import numpy as np

if len(sys.argv) != 3:
    print("Usage: " + sys.argv[0] + " <input_image> <output_image>")
    sys.exit(1)

input_file_name =  sys.argv[1]
output_file_name = sys.argv[2]

# Read input image
itk_image = itk.imread(input_file_name)

# Copy itk.Imag pixel data to numpy array
np_array = itk.array_from_image(itk_image)

# Convert the numpy array pixel data back to ITK
itk_np_copy = itk.image_from_array(np_array)

# Write out the numpy array as an ITK image
itk.imwrite(itk_np_copy,output_file_name)