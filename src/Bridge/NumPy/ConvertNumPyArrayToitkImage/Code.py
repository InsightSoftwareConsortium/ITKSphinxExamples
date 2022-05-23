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

# Parse comamnd line arguments
input_file_name = sys.argv[1]
output_file_name = sys.argv[2]

# Read input image
PixelType = itk.ctype("unsigned char")
ImageType = itk.Image[itk.UC, 2]
itk_image = itk.imread(input_file_name, PixelType)
OriginalRegion = itk_image.GetLargestPossibleRegion()
OriginalSize = OriginalRegion.GetSize()

print(f"The size of the ITK image data read from the input file  = {OriginalSize}\n")

# There are two ways to bridge the data structures.
# i) Give direct access to memory holding the data called "View" functions for displaying
# purpose. But you can't modify the data
np_view_array = itk.GetArrayViewFromImage(itk_image, ttype=ImageType)
print(f"The size of the NumPy array viewed from itk::Image = {np_view_array.shape}")

# ii) Generate a copy of the data using using array_from_image function.
#  You can then freely modify the data as it has no effect on the original ITK image.

# Copy itk.Image pixel data to numpy array
np_array = itk.GetArrayFromImage(itk_image, ttype=ImageType)
print(f"The size of the NumPy array copied from itk::Image = {np_array.shape}")

# Create an ITK image from the numpy array and then write it out
itk_np = itk.GetImageFromArray(np.ascontiguousarray(np_array))

region = itk_np.GetLargestPossibleRegion()
size = region.GetSize()
print(f"ITK image data size after convesion from NumPy = {size}\n")

itk.imwrite(itk_np, output_file_name)


# The order of the indexes is according to the type of object the data is stored in.
# A numpy array is indexed by [row , col ] for 2D data or [slice , row , col ] for 3D data.
# While ITK image data is indexed by (x , y ) for 2D or (x , y , z ) for 3D data.
# To demonstrate here, we create a 2D pixel array data
# and access a pixel with the same indices

np_data = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]], np.int32)
itk_np_view_data = itk.image_view_from_array(np_data)

print(f"ITK image data pixel value at [2,1] = {itk_np_view_data.GetPixel([2,1])}")
print(f"NumPy array pixel value at [2,1] = {np_data[2,1]}")
