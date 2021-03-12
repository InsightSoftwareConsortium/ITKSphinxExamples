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

if len(sys.argv) != 5:
    print(
        "Usage: "
        + sys.argv[0]
        + " <input_filename> <output_filename> <size_x> <size_y>"
    )
    sys.exit(1)

input_filename = sys.argv[1]
output_filename = sys.argv[2]
output_size = [int(sys.argv[3]), int(sys.argv[4])]

input_image = itk.imread(input_filename)

input_spacing = itk.spacing(input_image)
input_size = itk.size(input_image)
dimension = input_image.GetImageDimension()
output_spacing = [
    input_spacing[dim] * input_size[dim] / output_size[dim] for dim in range(dimension)
]

transform = itk.IdentityTransform[itk.D, dimension].New()

output_image = itk.resample_image_filter(
    input_image,
    size=output_size,
    output_spacing=output_spacing,
    output_origin=itk.origin(input_image),
    transform=transform,
)

itk.imwrite(output_image, output_filename)
