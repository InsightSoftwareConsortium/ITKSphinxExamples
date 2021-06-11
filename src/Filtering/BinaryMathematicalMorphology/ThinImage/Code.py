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

parser = argparse.ArgumentParser(description="Thin Image.")
parser.add_argument("input_image", nargs="?")
args = parser.parse_args()

PixelType = itk.UC
Dimension = 2
ImageType = itk.Image[PixelType, Dimension]

if args.input_image:
    image = itk.imread(args.input_image)

else:
    # Create an image
    start = itk.Index[Dimension]()
    start.Fill(0)

    size = itk.Size[Dimension]()
    size.Fill(100)

    region = itk.ImageRegion[Dimension]()
    region.SetIndex(start)
    region.SetSize(size)

    image = ImageType.New(Regions=region)
    image.Allocate()
    image.FillBuffer(0)

    # Draw a 5 pixel wide line
    image[50:55, 20:80] = 255

    # Write Image
    itk.imwrite(image, "input.png")

image = itk.binary_thinning_image_filter(image)

# Rescale the image so that it can be seen (the output is 0 and 1, we want 0 and 255)
image = itk.rescale_intensity_image_filter(image, output_minimum=0, output_maximum=255)

# Write Image
itk.imwrite(image, "outputPython.png")
