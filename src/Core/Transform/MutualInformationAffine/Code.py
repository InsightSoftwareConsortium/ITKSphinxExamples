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
fixed_image = itk.imread(sys.argv[1], itk.UC)
moving_image = itk.imread(sys.argv[2], itk.UC)

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

metric.SetNumberOfSpatialSamples(100)
metric.SetFixedImageStandardDeviation(5.0)
metric.SetMovingImageStandardDeviation(5.0)

metric.ReinitializeSeed(121212)

optimizer = itk.GradientDescentOptimizer.New()

optimizer.SetLearningRate(1.0)
optimizer.SetNumberOfIterations(200)
optimizer.MaximizeOff()

# Set scales so that the optimizer can take
# large steps along translation parameters,
# moderate steps along rotational parameters, and
# small steps along scale parameters
optimizer.SetScales([100, 0.5, 0.5, 100, 0.001, 0.001])

registrar = itk.ImageRegistrationMethod[type(fixed_image), type(moving_image)].New()
registrar.SetFixedImage(fixed_smoothed_image)
registrar.SetMovingImage(moving_smoothed_image)
registrar.SetTransform(transform)
registrar.SetInterpolator(interpolator)
registrar.SetMetric(metric)
registrar.SetOptimizer(optimizer)

registrar.SetFixedImageRegion(fixed_image.GetBufferedRegion())
registrar.SetInitialTransformParameters(transform.GetParameters())

registrar.Update()

# Print final results
print(f"Its: {optimizer.GetCurrentIteration()}")
print(f"Final Value: {optimizer.GetValue()}")
print(f"Final Position: {list(registrar.GetLastTransformParameters())}")

# Resample and write out image
ResampleFilterType = itk.ResampleImageFilter[type(fixed_image), type(fixed_image)]
resample = ResampleFilterType.New(
    Transform=transform,
    Input=moving_image,
    Size=fixed_image.GetLargestPossibleRegion().GetSize(),
    OutputOrigin=fixed_image.GetOrigin(),
    OutputSpacing=fixed_image.GetSpacing(),
    OutputDirection=fixed_image.GetDirection(),
    DefaultPixelValue=100,
)

resample.Update()

itk.imwrite(resample.GetOutput(), sys.argv[3])
