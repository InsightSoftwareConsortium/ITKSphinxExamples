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

input_file_name = sys.argv[1]
output_file_name = sys.argv[2]
scale = float(sys.argv[3])

input_image = itk.imread(input_file_name)
input_size = itk.size(input_image)
input_spacing = itk.spacing(input_image)
input_origin = itk.origin(input_image)
Dimension = input_image.GetImageDimension()

# We will scale the objects in the image by the factor `scale`; that is they
# will be shrunk (scale < 1.0) or enlarged (scale > 1.0).  However, the number
# of pixels for each dimension of the output image will equal the corresponding
# number of pixels in the input image, with cropping or padding as necessary.
# Furthermore, the physical distance between adjacent pixels will be the same
# in the input and the output images.  In contrast, if you want to change the
# resolution of the image without changing the represented physical size of the
# objects in the image, omit the transform and instead supply:
#
# output_size = [int(input_size[d] * scale) for d in range(Dimension)]
# output_spacing = [input_spacing[d] / scale for d in range(Dimension)]
# output_origin = [input_origin[d] + 0.5 * (output_spacing[d] - input_spacing[d])
#                  for d in range(Dimension)]

output_size = input_size
output_spacing = input_spacing
output_origin = input_origin
scale_transform = itk.ScaleTransform[itk.D, Dimension].New()
scale_transform_parameters = scale_transform.GetParameters()
for i in range(len(scale_transform_parameters)):
    scale_transform_parameters[i] = scale
scale_transform_center = [float(int(s / 2)) for s in input_size]
scale_transform.SetParameters(scale_transform_parameters)
scale_transform.SetCenter(scale_transform_center)

interpolator = itk.LinearInterpolateImageFunction.New(input_image)

resampled = itk.resample_image_filter(
    input_image,
    transform=scale_transform,
    interpolator=interpolator,
    size=output_size,
    output_spacing=output_spacing,
    output_origin=output_origin,
)

itk.imwrite(resampled, output_file_name)
