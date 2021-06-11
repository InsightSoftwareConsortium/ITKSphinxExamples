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
import argparse

parser = argparse.ArgumentParser(
    description="Combine Two Images With Checker Board Pattern."
)
parser.add_argument("output_image")
args = parser.parse_args()

dimension = 2
pixel_type = itk.UC
image_type = itk.Image[pixel_type, dimension]

# Create an image
start = itk.Index[dimension]()
start.Fill(0)

size = itk.Size[dimension]()
size.Fill(100)

region = itk.ImageRegion[dimension]()
region.SetSize(size)
region.SetIndex(start)

image1 = image_type.New(Regions=region)
image1.Allocate()
image1.FillBuffer(0)

image2 = image_type.New(Regions=region)
image2.Allocate()
image2.FillBuffer(255)

output = itk.checker_board_image_filter(image1, image2)

itk.imwrite(output, args.output_image)
