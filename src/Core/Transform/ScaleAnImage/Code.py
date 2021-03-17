#!/usr/bin/env python

# =========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
# =========================================================================*/

import sys

import itk

if len(sys.argv) < 3:
    raise Exception(f"Usage: {sys.argv[0]} inputFile outputFile")

image = itk.imread(sys.argv[1], itk.UC)

image_dimension = image.GetImageDimension()

transform = itk.ScaleTransform[itk.D, 2].New(
    scale=[1.5] * image_dimension, center=[x / 2 for x in itk.size(image)]
)

scaled_image = itk.resample_image_filter(
    image, transform=transform, size=itk.size(image)
)

itk.imwrite(scaled_image, sys.argv[2])
