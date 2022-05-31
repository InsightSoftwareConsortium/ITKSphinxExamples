#!/usr/bin/env python

# Copyright NumFOCUS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#        https://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys
import itk
import argparse

from distutils.version import StrictVersion as VS

if VS(itk.Version.GetITKVersion()) < VS("4.9.0"):
    print("ITK 4.9.0 is required.")
    sys.exit(1)

parser = argparse.ArgumentParser(
    description="Perform 2D Translation Registration With Mean Squares."
)
parser.add_argument("fixed_input_image")
parser.add_argument("moving_input_image")
parser.add_argument("output_image")
parser.add_argument("difference_image_after")
parser.add_argument("difference_image_before")
args = parser.parse_args()

PixelType = itk.ctype("float")

fixedImage = itk.imread(args.fixed_input_image, PixelType)
movingImage = itk.imread(args.moving_input_image, PixelType)

Dimension = fixedImage.GetImageDimension()
FixedImageType = itk.Image[PixelType, Dimension]
MovingImageType = itk.Image[PixelType, Dimension]

TransformType = itk.TranslationTransform[itk.D, Dimension]
initialTransform = TransformType.New()

optimizer = itk.RegularStepGradientDescentOptimizerv4.New(
    LearningRate=4,
    MinimumStepLength=0.001,
    RelaxationFactor=0.5,
    NumberOfIterations=200,
)

metric = itk.MeanSquaresImageToImageMetricv4[FixedImageType, MovingImageType].New()

registration = itk.ImageRegistrationMethodv4.New(
    FixedImage=fixedImage,
    MovingImage=movingImage,
    Metric=metric,
    Optimizer=optimizer,
    InitialTransform=initialTransform,
)

movingInitialTransform = TransformType.New()
initialParameters = movingInitialTransform.GetParameters()
initialParameters[0] = 0
initialParameters[1] = 0
movingInitialTransform.SetParameters(initialParameters)
registration.SetMovingInitialTransform(movingInitialTransform)

identityTransform = TransformType.New()
identityTransform.SetIdentity()
registration.SetFixedInitialTransform(identityTransform)

registration.SetNumberOfLevels(1)
registration.SetSmoothingSigmasPerLevel([0])
registration.SetShrinkFactorsPerLevel([1])

registration.Update()

transform = registration.GetTransform()
finalParameters = transform.GetParameters()
translationAlongX = finalParameters.GetElement(0)
translationAlongY = finalParameters.GetElement(1)

numberOfIterations = optimizer.GetCurrentIteration()

bestValue = optimizer.GetValue()

print("Result = ")
print(" Translation X = " + str(translationAlongX))
print(" Translation Y = " + str(translationAlongY))
print(" Iterations    = " + str(numberOfIterations))
print(" Metric value  = " + str(bestValue))

CompositeTransformType = itk.CompositeTransform[itk.D, Dimension]
outputCompositeTransform = CompositeTransformType.New()
outputCompositeTransform.AddTransform(movingInitialTransform)
outputCompositeTransform.AddTransform(registration.GetModifiableTransform())

resampler = itk.ResampleImageFilter.New(
    Input=movingImage,
    Transform=outputCompositeTransform,
    UseReferenceImage=True,
    ReferenceImage=fixedImage,
)
resampler.SetDefaultPixelValue(100)

OutputPixelType = itk.ctype("unsigned char")
OutputImageType = itk.Image[OutputPixelType, Dimension]

caster = itk.CastImageFilter[FixedImageType, OutputImageType].New(Input=resampler)

writer = itk.ImageFileWriter.New(Input=caster, FileName=args.output_image)
writer.Update()

difference = itk.SubtractImageFilter.New(Input1=fixedImage, Input2=resampler)

intensityRescaler = itk.RescaleIntensityImageFilter[
    FixedImageType, OutputImageType
].New(
    Input=difference,
    OutputMinimum=itk.NumericTraits[OutputPixelType].min(),
    OutputMaximum=itk.NumericTraits[OutputPixelType].max(),
)

resampler.SetDefaultPixelValue(1)
writer.SetInput(intensityRescaler.GetOutput())
writer.SetFileName(args.difference_image_after)
writer.Update()

resampler.SetTransform(identityTransform)
writer.SetFileName(args.difference_image_before)
writer.Update()
