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

parser = argparse.ArgumentParser(description="Compute Inverse FFT Of Image.")
parser.add_argument("input_image", nargs="?")
args = parser.parse_args()

dimension = 2
float_image_type = itk.Image[itk.F, dimension]

if not args.input_image:
    corner = itk.Index[dimension]()
    corner.Fill(0)

    size = itk.Size[dimension]()
    size.Fill(200)

    region = itk.ImageRegion[dimension]()
    region.SetIndex(corner)
    region.SetSize(size)

    image = float_image_type.New(Regions=region)
    image.Allocate()
    image.FillBuffer(0)

    # Make a square
    image[40:100, 40:100] = 100

else:
    image = itk.imread(args.input_image, pixel_type=itk.F)

# Define some types
unsigned_char_image_type = itk.Image[itk.UC, dimension]

# Compute the FFT
image = itk.forward_fft_image_filter(image)

# Compute the IFFT
image = itk.inverse_fft_image_filter(image)

image = itk.cast_image_filter(image, ttype=(float_image_type, unsigned_char_image_type))

itk.imwrite(image, "ComputeInverseFFTOfImagePython.png")
