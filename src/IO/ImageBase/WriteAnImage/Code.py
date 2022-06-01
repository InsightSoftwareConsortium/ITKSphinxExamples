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
import argparse

parser = argparse.ArgumentParser(description="Write An Image.")
parser.add_argument("output_image", nargs="?")
args = parser.parse_args()

if args.output_image:
    output_filename = args.output_image
else:
    output_filename = "testPython.png"

pixel_type = itk.UC
dimension = 2
image_type = itk.Image[pixel_type, dimension]

start = itk.Index[dimension]()
start.Fill(0)

size = itk.Size[dimension]()
size[0] = 200
size[1] = 300

region = itk.ImageRegion[dimension]()
region.SetIndex(start)
region.SetSize(size)

image = image_type.New(Regions=region)
image.Allocate()

itk.imwrite(image, output_filename)
