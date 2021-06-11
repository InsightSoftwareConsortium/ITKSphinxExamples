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

parser = argparse.ArgumentParser(description="Rescale Intensity.")
parser.add_argument("input_image")
parser.add_argument("output_image")
parser.add_argument("output_min", type=int)
parser.add_argument("output_max", type=int)
args = parser.parse_args()

image = itk.imread(args.input_image)

image = itk.rescale_intensity_image_filter(
    image, output_minimum=args.output_min, output_maximum=args.output_max
)

itk.imwrite(image, args.output_image)
