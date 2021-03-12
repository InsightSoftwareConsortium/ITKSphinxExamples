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

import sys
import itk

if len(sys.argv) != 4:
    print("Usage: " + sys.argv[0] + " <input_image> <output_image> <scale>")
    sys.exit(1)

input_image = sys.argv[1]
output_image = sys.argv[2]
scale = float(sys.argv[3])

input_image = itk.imread(input_image)

size = itk.size(input_image)
spacing = itk.spacing(input_image)

central_pixel = [int(s / 2) for s in size]
central_point = [float(p) for p in central_pixel]

Dimension = input_image.GetImageDimension()
scale_transform = itk.ScaleTransform[itk.D, Dimension].New()

parameters = scale_transform.GetParameters()
for i in range(len(parameters)):
    parameters[i] = scale

scale_transform.SetParameters(parameters)
scale_transform.SetCenter(central_point)

interpolator = itk.LinearInterpolateImageFunction.New(input_image)

resampled = itk.resample_image_filter(
    input_image,
    transform=scale_transform,
    interpolator=interpolator,
    size=size,
    output_spacing=spacing,
)

itk.imwrite(resampled, output_image)
