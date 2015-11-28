#!/usr/bin/env python

#==========================================================================
#
#   Copyright Insight Software Consortium
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
#==========================================================================*/

import sys
import itk

if len(sys.argv) != 11:
    print(
        "Usage: " + sys.argv[0] + "<InputFileName>  <OutputFileName>"
        " <seedX> <seedY> <InitialDistance> <Sigma> <SigmoidAlpha> "
        "<SigmoidBeta> <PropagationScaling> <NumberOfIterations>")
    sys.exit(1)

inputFileName = sys.argv[1]
outputFileName = sys.argv[2]
seedPosX = int(sys.argv[3])
seedPosY = int(sys.argv[4])

initialDistance = float(sys.argv[5])
sigma = float(sys.argv[6])
alpha = float(sys.argv[7])
beta = float(sys.argv[8])
propagationScaling = float(sys.argv[9])
numberOfIterations = int(sys.argv[10])
seedValue = -initialDistance

Dimension = 2

InputPixelType = itk.F
OutputPixelType = itk.UC

InputImageType = itk.Image[InputPixelType, Dimension]
OutputImageType = itk.Image[OutputPixelType, Dimension]

ReaderType = itk.ImageFileReader[InputImageType]
WriterType = itk.ImageFileWriter[OutputImageType]

reader = ReaderType.New()
reader.SetFileName(inputFileName)

SmoothingFilterType = itk.CurvatureAnisotropicDiffusionImageFilter[
    InputImageType, InputImageType]
smoothing = SmoothingFilterType.New()
smoothing.SetTimeStep(0.125)
smoothing.SetNumberOfIterations(5)
smoothing.SetConductanceParameter(9.0)
smoothing.SetInput(reader.GetOutput())

GradientFilterType = itk.GradientMagnitudeRecursiveGaussianImageFilter[
    InputImageType, InputImageType]
gradientMagnitude = GradientFilterType.New()
gradientMagnitude.SetSigma(sigma)
gradientMagnitude.SetInput(smoothing.GetOutput())

SigmoidFilterType = itk.SigmoidImageFilter[InputImageType, InputImageType]
sigmoid = SigmoidFilterType.New()
sigmoid.SetOutputMinimum(0.0)
sigmoid.SetOutputMaximum(1.0)
sigmoid.SetAlpha(alpha)
sigmoid.SetBeta(beta)
sigmoid.SetInput(gradientMagnitude.GetOutput())

FastMarchingFilterType = itk.FastMarchingImageFilter[
    InputImageType, InputImageType]
fastMarching = FastMarchingFilterType.New()

GeoActiveContourFilterType = itk.GeodesicActiveContourLevelSetImageFilter[
    InputImageType, InputImageType, InputPixelType]
geodesicActiveContour = GeoActiveContourFilterType.New()
geodesicActiveContour.SetPropagationScaling(propagationScaling)
geodesicActiveContour.SetCurvatureScaling(1.0)
geodesicActiveContour.SetAdvectionScaling(1.0)
geodesicActiveContour.SetMaximumRMSError(0.02)
geodesicActiveContour.SetNumberOfIterations(numberOfIterations)
geodesicActiveContour.SetInput(fastMarching.GetOutput())
geodesicActiveContour.SetFeatureImage(sigmoid.GetOutput())

ThresholdingFilterType = itk.BinaryThresholdImageFilter[
    InputImageType, OutputImageType]
thresholder = ThresholdingFilterType.New()
thresholder.SetLowerThreshold(-1000.0)
thresholder.SetUpperThreshold(0.0)
thresholder.SetOutsideValue(itk.NumericTraits[OutputPixelType].min())
thresholder.SetInsideValue(itk.NumericTraits[OutputPixelType].max())
thresholder.SetInput(geodesicActiveContour.GetOutput())

seedPosition = itk.Index[Dimension]()
seedPosition[0] = seedPosX
seedPosition[1] = seedPosY

node = itk.LevelSetNode[InputPixelType, Dimension]()
node.SetValue(seedValue)
node.SetIndex(seedPosition)

seeds = itk.VectorContainer[
    itk.UI, itk.LevelSetNode[InputPixelType, Dimension]].New()
seeds.Initialize()
seeds.InsertElement(0, node)

fastMarching.SetTrialPoints(seeds)
fastMarching.SetSpeedConstant(1.0)

CastFilterType = itk.RescaleIntensityImageFilter[
    InputImageType, OutputImageType]

caster1 = CastFilterType.New()
caster2 = CastFilterType.New()
caster3 = CastFilterType.New()
caster4 = CastFilterType.New()

writer1 = WriterType.New()
writer2 = WriterType.New()
writer3 = WriterType.New()
writer4 = WriterType.New()

caster1.SetInput(smoothing.GetOutput())
writer1.SetInput(caster1.GetOutput())
writer1.SetFileName("GeodesicActiveContourImageFilterOutput1.png")
caster1.SetOutputMinimum(itk.NumericTraits[OutputPixelType].min())
caster1.SetOutputMaximum(itk.NumericTraits[OutputPixelType].max())
writer1.Update()

caster2.SetInput(gradientMagnitude.GetOutput())
writer2.SetInput(caster2.GetOutput())
writer2.SetFileName("GeodesicActiveContourImageFilterOutput2.png")
caster2.SetOutputMinimum(itk.NumericTraits[OutputPixelType].min())
caster2.SetOutputMaximum(itk.NumericTraits[OutputPixelType].max())
writer2.Update()

caster3.SetInput(sigmoid.GetOutput())
writer3.SetInput(caster3.GetOutput())
writer3.SetFileName("GeodesicActiveContourImageFilterOutput3.png")
caster3.SetOutputMinimum(itk.NumericTraits[OutputPixelType].min())
caster3.SetOutputMaximum(itk.NumericTraits[OutputPixelType].max())
writer3.Update()

caster4.SetInput(fastMarching.GetOutput())
writer4.SetInput(caster4.GetOutput())
writer4.SetFileName("GeodesicActiveContourImageFilterOutput4.png")
caster4.SetOutputMinimum(itk.NumericTraits[OutputPixelType].min())
caster4.SetOutputMaximum(itk.NumericTraits[OutputPixelType].max())

fastMarching.SetOutputSize(
    reader.GetOutput().GetBufferedRegion().GetSize())

writer = WriterType.New()
writer.SetFileName(outputFileName)
writer.SetInput(thresholder.GetOutput())
writer.Update()

print(
    "Max. no. iterations: " +
    str(geodesicActiveContour.GetNumberOfIterations()) + "\n")
print(
    "Max. RMS error: " +
    str(geodesicActiveContour.GetMaximumRMSError()) + "\n")
print(
    "No. elpased iterations: " +
    str(geodesicActiveContour.GetElapsedIterations()) + "\n")
print("RMS change: " + str(geodesicActiveContour.GetRMSChange()) + "\n")

writer4.Update()

InternalWriterType = itk.ImageFileWriter[InputImageType]

mapWriter = InternalWriterType.New()
mapWriter.SetInput(fastMarching.GetOutput())
mapWriter.SetFileName("GeodesicActiveContourImageFilterOutput4.mha")
mapWriter.Update()

speedWriter = InternalWriterType.New()
speedWriter.SetInput(sigmoid.GetOutput())
speedWriter.SetFileName("GeodesicActiveContourImageFilterOutput3.mha")
speedWriter.Update()

gradientWriter = InternalWriterType.New()
gradientWriter.SetInput(gradientMagnitude.GetOutput())
gradientWriter.SetFileName("GeodesicActiveContourImageFilterOutput2.mha")
gradientWriter.Update()
