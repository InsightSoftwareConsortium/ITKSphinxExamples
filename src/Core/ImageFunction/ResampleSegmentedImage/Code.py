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
import sys

if len(sys.argv) != 6:
    print(f"Usage: {sys.argv[0]} input_image_file spacing_fraction sigma_fraction output_image_file_label_image_interpolator output_image_file_nearest_neighbor_interpolator")
    sys.exit(1)

input_image_file = sys.argv[1]
spacing_fraction = float(sys.argv[2])
sigma_fraction = float(sys.argv[3])
output_image_file_label_image_interpolator = sys.argv[4]
output_image_file_nearest_neighbor_interpolator = sys.argv[5]

input_image = itk.imread(input_image_file)

resize_filter = itk.ResampleImageFilter.New(input_image)

input_spacing = itk.spacing(input_image)
output_spacing = [s * spacing_fraction for s in input_spacing]
resize_filter.SetOutputSpacing(output_spacing)

input_size = itk.size(input_image)
output_size = [int(s * input_spacing[dim] / spacing_fraction) for dim, s in
        enumerate(input_size)]
resize_filter.SetSize(output_size)

gaussian_interpolator = itk.LabelImageGaussianInterpolateImageFunction.New(input_image)
sigma = [s * sigma_fraction for s in output_spacing]
gaussian_interpolator.SetSigma(sigma)
gaussian_interpolator.SetAlpha(3.0)
resize_filter.SetInterpolator(gaussian_interpolator)

itk.imwrite(resize_filter, output_image_file_label_image_interpolator)

nearest_neighbor_interpolator = itk.NearestNeighborInterpolateImageFunction.New(input_image)
resize_filter.SetInterpolator(nearest_neighbor_interpolator)

itk.imwrite(resize_filter, output_image_file_nearest_neighbor_interpolator)
