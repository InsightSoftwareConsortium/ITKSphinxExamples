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

if len(sys.argv) != 3:
    print("Usage: " + sys.argv[0] + " [input_filename] [output_filename]")
    sys.exit(1)

input_filename = sys.argv[1]
output_filename = sys.argv[2]

PixelType = itk.RGBPixel[itk.UC]

input_image = itk.imread(input_filename, pixel_type=PixelType)

ImageType = type(input_image)
interpolator = itk.LinearInterpolateImageFunction[ImageType, itk.D].New()

Dimension = input_image.GetImageDimension()
transform = itk.IdentityTransform[itk.D, Dimension].New()

output_image = itk.resample_image_filter(
    input_image,
    interpolator=interpolator,
    transform=transform,
    default_pixel_value=[50, 50, 50],
    output_spacing=[0.5, 0.5],
    output_origin=[30, 40],
    size=[300, 300],
)

itk.imwrite(output_image, output_filename)
