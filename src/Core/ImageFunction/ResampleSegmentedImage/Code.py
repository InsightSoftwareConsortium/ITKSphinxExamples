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

parser = argparse.ArgumentParser(description="Resample Segmented Image.")
parser.add_argument("input_image")
parser.add_argument("spacing_fraction", type=float)
parser.add_argument("sigma_fraction", type=float)
parser.add_argument("output_image_file_label_image_interpolator")
parser.add_argument("output_image_file_nearest_neighbor_interpolator")
args = parser.parse_args()

input_image = itk.imread(args.input_image)

resize_filter = itk.ResampleImageFilter.New(input_image)

input_spacing = itk.spacing(input_image)
output_spacing = [s * args.spacing_fraction for s in input_spacing]
resize_filter.SetOutputSpacing(output_spacing)

input_size = itk.size(input_image)
output_size = [
    int(s * input_spacing[dim] / args.spacing_fraction)
    for dim, s in enumerate(input_size)
]
resize_filter.SetSize(output_size)

gaussian_interpolator = itk.LabelImageGaussianInterpolateImageFunction.New(input_image)
sigma = [s * args.sigma_fraction for s in output_spacing]
gaussian_interpolator.SetSigma(sigma)
gaussian_interpolator.SetAlpha(3.0)
resize_filter.SetInterpolator(gaussian_interpolator)

itk.imwrite(resize_filter, args.output_image_file_label_image_interpolator)

nearest_neighbor_interpolator = itk.NearestNeighborInterpolateImageFunction.New(
    input_image
)
resize_filter.SetInterpolator(nearest_neighbor_interpolator)

itk.imwrite(resize_filter, args.output_image_file_nearest_neighbor_interpolator)
