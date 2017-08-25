#!/usr/bin/env python

# Copyright Insight Software Consortium
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

from distutils.version import StrictVersion as VS
if VS(itk.Version.GetITKVersion()) < VS("4.9.0"):
    print("ITK 4.9.0 is required.")
    sys.exit(1)

if len(sys.argv) != 6:
    print("Usage: " + sys.argv[0] + " <fixedImageFile> <movingImageFile> "
          "<outputImagefile> <differenceImageAfter> <differenceImageBefore>")
    sys.exit(1)

fixedImage = sys.argv[1]
movingImage = sys.argv[2]
outputImage = sys.argv[3]
differenceImageAfter = sys.argv[4]
differenceImageBefore = sys.argv[5]

Dimension = 2
PixelType = itk.F

FixedImageType = itk.Image[PixelType, Dimension]
MovingImageType = itk.Image[PixelType, Dimension]

TransformType = itk.TranslationTransform[itk.D, Dimension]
OptimizerType = itk.RegularStepGradientDescentOptimizerv4[itk.D]

MetricType = itk.MeanSquaresImageToImageMetricv4[
    FixedImageType, MovingImageType]

RegistrationType = itk.ImageRegistrationMethodv4[
    FixedImageType, MovingImageType]

metric = MetricType.New()
optimizer = OptimizerType.New()
transform = TransformType.New()
registration = RegistrationType.New()

registration.SetMetric(metric)
registration.SetOptimizer(optimizer)
registration.SetInitialTransform(transform)

FixedLinearInterpolatorType = itk.LinearInterpolateImageFunction[
    FixedImageType, itk.D]
MovingLinearInterpolatorType = itk.LinearInterpolateImageFunction[
    MovingImageType, itk.D]

fixedInterpolator = FixedLinearInterpolatorType.New()
movingInterpolator = MovingLinearInterpolatorType.New()

metric.SetFixedInterpolator(fixedInterpolator)
metric.SetMovingInterpolator(movingInterpolator)

FixedImageReaderType = itk.ImageFileReader[FixedImageType]
MovingImageReaderType = itk.ImageFileReader[MovingImageType]
fixedImageReader = FixedImageReaderType.New()
movingImageReader = MovingImageReaderType.New()

fixedImageReader.SetFileName(fixedImage)
movingImageReader.SetFileName(movingImage)

registration.SetFixedImage(fixedImageReader.GetOutput())
registration.SetMovingImage(movingImageReader.GetOutput())

movingInitialTransform = TransformType.New()
initialParameters = movingInitialTransform.GetParameters()
initialParameters[0] = 0
initialParameters[1] = 0
movingInitialTransform.SetParameters(initialParameters)

registration.SetMovingInitialTransform(movingInitialTransform)

identityTransform = TransformType.New()
identityTransform.SetIdentity()

registration.SetFixedInitialTransform(identityTransform)

optimizer.SetLearningRate(4)
optimizer.SetMinimumStepLength(0.001)
optimizer.SetRelaxationFactor(0.5)
optimizer.SetNumberOfIterations(200)

registration.SetNumberOfLevels(1)
registration.SetSmoothingSigmasPerLevel([0])
registration.SetShrinkFactorsPerLevel([1])

registration.Update()

transform = registration.GetTransform()

finalParameters = transform.GetParameters()
TranslationAlongX = finalParameters.GetElement(0)
TranslationAlongY = finalParameters.GetElement(1)

numberOfIterations = optimizer.GetCurrentIteration()

bestValue = optimizer.GetValue()

print("Result = ")
print(" Translation X = " + str(TranslationAlongX))
print(" Translation Y = " + str(TranslationAlongY))
print(" Iterations    = " + str(numberOfIterations))
print(" Metric value  = " + str(bestValue))

CompositeTransformType = itk.CompositeTransform[itk.D, Dimension]
outputCompositeTransform = CompositeTransformType.New()
outputCompositeTransform.AddTransform(movingInitialTransform)
outputCompositeTransform.AddTransform(registration.GetModifiableTransform())

ResampleFilterType = itk.ResampleImageFilter[MovingImageType, FixedImageType]
resampler = ResampleFilterType.New()
resampler.SetInput(movingImageReader.GetOutput())
resampler.SetTransform(outputCompositeTransform)

fixedImage = fixedImageReader.GetOutput()
resampler.SetSize(fixedImage.GetLargestPossibleRegion().GetSize())
resampler.SetOutputOrigin(fixedImage.GetOrigin())
resampler.SetOutputSpacing(fixedImage.GetSpacing())
resampler.SetOutputDirection(fixedImage.GetDirection())
resampler.SetDefaultPixelValue(100)

OutputPixelType = itk.UC
OutputImageType = itk.Image[OutputPixelType, Dimension]

CastFilterType = itk.CastImageFilter[FixedImageType, OutputImageType]
WriterType = itk.ImageFileWriter[OutputImageType]

writer = WriterType.New()
caster = CastFilterType.New()

writer.SetFileName(outputImage)

caster.SetInput(resampler.GetOutput())
writer.SetInput(caster.GetOutput())
writer.Update()

DifferenceFilterType = itk.SubtractImageFilter[
    FixedImageType, FixedImageType, FixedImageType]

difference = DifferenceFilterType.New()

difference.SetInput1(fixedImageReader.GetOutput())
difference.SetInput2(resampler.GetOutput())

RescalerType = itk.RescaleIntensityImageFilter[FixedImageType, OutputImageType]
intensityRescaler = RescalerType.New()

intensityRescaler.SetInput(difference.GetOutput())
intensityRescaler.SetOutputMinimum(itk.NumericTraits[OutputPixelType].min())
intensityRescaler.SetOutputMaximum(itk.NumericTraits[OutputPixelType].max())

resampler.SetDefaultPixelValue(1)

writer2 = WriterType.New()
writer2.SetInput(intensityRescaler.GetOutput())

writer2.SetFileName(differenceImageAfter)
writer2.Update()

resampler.SetTransform(identityTransform)

writer2.SetFileName(differenceImageBefore)
writer2.Update()
