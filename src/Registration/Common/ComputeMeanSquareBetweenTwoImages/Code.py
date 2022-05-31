#!/usr/bin/env python3

# =========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          https://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
# =========================================================================*/

import itk
import argparse

parser = argparse.ArgumentParser(description="Compute Mean Square Between Two Images.")
parser.add_argument("input_image_1")
parser.add_argument("input_image_2")
args = parser.parse_args()

fixed_image = itk.imread(args.input_image_1, itk.F)
moving_image = itk.imread(args.input_image_2, itk.F)

metric = itk.MeanSquaresImageToImageMetric[type(fixed_image), type(moving_image)].New()
transform = itk.TranslationTransform[itk.D, fixed_image.GetImageDimension()].New()
interpolator = itk.LinearInterpolateImageFunction[type(fixed_image), itk.D].New()

metric.SetFixedImage(fixed_image)
metric.SetMovingImage(moving_image)
metric.SetFixedImageRegion(fixed_image.GetLargestPossibleRegion())
metric.SetTransform(transform)
metric.SetInterpolator(interpolator)
metric.Initialize()

params = itk.OptimizerParameters[itk.D]()
params.SetSize(2)

for x in range(-10, 15, 5):
    params.SetElement(0, x)
    for y in range(-10, 15, 5):
        params.SetElement(1, y)
        print(f"{list(params)}: {metric.GetValue(params):.1f}")
