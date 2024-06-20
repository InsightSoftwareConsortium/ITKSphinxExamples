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

parser = argparse.ArgumentParser(description="Compute Inverse FFT Of Image.")
parser.add_argument("input_path", nargs=1, type=str)
parser.add_argument("modulus_output_path", nargs=1, type=str)
parser.add_argument("phase_output_path", nargs=1, type=str)
parser.add_argument("fft_direction", nargs="?", default=0, type=int)
args = parser.parse_args()

# Read input image
pixel_type = itk.F
image = itk.imread(args.input_path[0], pixel_type=pixel_type)
print(f"Read real input image of type {type(image)} and size {itk.size(image)}")

assert (
    args.fft_direction < image.GetImageDimension()
), "FFT direction must be an image dimension"

# Perform FFT in given direction
padded_image = itk.fft_pad_image_filter(image)
print(f"Padded input image to size {itk.size(image)}")
print(f"Performing FFT along axis {args.fft_direction}")
complex_image = itk.forward1_dfft_image_filter(image, direction=args.fft_direction)
print(
    f"Generated complex frequency image of type {type(complex_image)} and size {itk.size(complex_image)}"
)

# Shift image along FFT dimension to represent complex range (-f_B, +f_B]
shift = [0] * complex_image.GetImageDimension()
shift[args.fft_direction] = int(itk.size(complex_image)[args.fft_direction] / 2)
shift = [int(itk.size(complex_image)[args.fft_direction] / 2), 0]
shifted_image = itk.cyclic_shift_image_filter(complex_image, shift=shift)

# Write out modulus and phase images for visualization in PNG format
modulus_image = itk.complex_to_modulus_image_filter(shifted_image)
itk.imwrite(modulus_image, args.modulus_output_path[0])

phase_image = itk.complex_to_phase_image_filter(shifted_image)
itk.imwrite(phase_image, args.phase_output_path[0])
