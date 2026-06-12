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

import sys
import itk

dimension = 2
float_image_type = itk.Image[itk.F, dimension]
unsigned_char_image_type = itk.Image[itk.UC, dimension]

start = itk.Index[dimension]()
start.Fill(0)

size = itk.Size[dimension]()
size.Fill(100)

region = itk.ImageRegion[dimension]()
region.SetIndex(start)
region.SetSize(size)

image = float_image_type.New(Regions=region)
image.Allocate()
image.FillBuffer(0)

image[20:80, 20:80] = 15

input_image = itk.rescale_intensity_image_filter(
    image,
    output_minimum=0,
    output_maximum=255,
    ttype=(float_image_type, unsigned_char_image_type),
)

itk.imwrite(input_image, "inputPython.png")

sobel_operator = itk.SobelOperator[itk.F, dimension]()
radius = itk.Size[dimension]()
radius.Fill(1)  # a radius of 1x1 creates a 3x3 operator
sobel_operator.SetDirection(0)  # Create the operator for the X axis derivative
sobel_operator.CreateToRadius(radius)

image = itk.neighborhood_operator_image_filter(image, operator=sobel_operator)

output_image = itk.rescale_intensity_image_filter(
    image,
    output_minimum=0,
    output_maximum=255,
    ttype=(float_image_type, unsigned_char_image_type),
)

itk.imwrite(output_image, "outputPython.png")
