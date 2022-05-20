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
    description="Smoothing Image With Discrete Gaussian Filter."
)
parser.add_argument("input_image")
parser.add_argument("output_image")
parser.add_argument("sigma", type=float)
args = parser.parse_args()

image = itk.imread(args.input_image)

smooth_image = itk.discrete_gaussian_image_filter(image, sigma=args.sigma)

itk.imwrite(smooth_image, args.output_image)
