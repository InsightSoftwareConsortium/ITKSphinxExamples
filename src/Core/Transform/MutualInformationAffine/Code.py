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
import numpy as np

import itk

if len(sys.argv) < 4:
    raise Exception(f"Usage: {sys.argv[0]} fixed_image moving_image output_image")

# Import images
fixed_image = itk.imread(sys.argv[1], itk.SS)
moving_image = itk.imread(sys.argv[2], itk.SS)

# Preprocess images
fixed_normalized_image = itk.normalize_image_filter(fixed_image)
fixed_smoothed_image = itk.discrete_gaussian_image_filter(
    fixed_normalized_image, variance=2.0
)

moving_normalized_image = itk.normalize_image_filter(moving_image)
moving_smoothed_image = itk.discrete_gaussian_image_filter(
    moving_normalized_image, variance=2.0
)

# Run gradient ascent
transform = itk.AffineTransform[itk.D, fixed_image.GetImageDimension()].New()
interpolator = itk.LinearInterpolateImageFunction[type(fixed_image), itk.D].New()

metric = itk.MutualInformationImageToImageMetric[
    type(fixed_image), type(moving_image)
].New()

number_of_pixels = fixed_image.GetBufferedRegion().GetNumberOfPixels()
number_of_samples = int(number_of_pixels * 0.01)
metric.SetNumberOfSpatialSamples(number_of_samples)

metric.SetFixedImageStandardDeviation(25.0)
metric.SetMovingImageStandardDeviation(25.0)

metric.ReinitializeSeed(121212)

optimizer = itk.GradientDescentOptimizer.New()

optimizer.SetLearningRate(1.0)
optimizer.SetNumberOfIterations(200)
optimizer.MaximizeOff()

# Set scales so that the optimizer can take
# large steps along translation parameters,
# moderate steps along rotational parameters, and
# small steps along scale parameters
optimizer.SetScales([100, 100, 100, 100, 0.01, 0.01])

result_object = itk.image_registration_method(
    fixed_image=fixed_image,
    moving_image=moving_image,
    transform=transform,
    interpolator=interpolator,
    metric=metric,
    optimizer=optimizer,
    fixed_image_region=fixed_image.GetBufferedRegion(),
    initial_transform_parameters=transform.GetParameters(),
)

# Print final results
print("Number of samples: " + str(number_of_samples))
print(f"Its: {optimizer.GetCurrentIteration()}")
print(f"Final Value: {optimizer.GetValue()}")
print(f"Final Position: {list(transform.GetParameters())}")

# Resample and write out image
resampled = itk.resample_image_filter(
    input=moving_image,
    transform=result_object,
    size=fixed_image.GetLargestPossibleRegion().GetSize(),
    output_origin=fixed_image.GetOrigin(),
    output_spacing=fixed_image.GetSpacing(),
    output_direction=fixed_image.GetDirection(),
    default_pixel_value=100,
)

itk.imwrite(resampled, sys.argv[3])
