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
import argparse

parser = argparse.ArgumentParser(
    description="Compute Perona Malik Anisotropic Diffusion."
)
parser.add_argument("input_image")
parser.add_argument("output_image")
parser.add_argument("number_of_iterations", type=int)
parser.add_argument("conductance", type=float)
args = parser.parse_args()


Dimension = 2
InputPixelType = itk.UC
InputImageType = itk.Image[InputPixelType, Dimension]
OutputPixelType = itk.F
OutputImageType = itk.Image[OutputPixelType, Dimension]

ReaderType = itk.ImageFileReader[InputImageType]
reader = ReaderType.New()
reader.SetFileName(args.input_image)

CastFilterType = itk.CastImageFilter[InputImageType, OutputImageType]
castfilter = CastFilterType.New()
castfilter.SetInput(reader)

FilterType = itk.GradientAnisotropicDiffusionImageFilter[
    OutputImageType, OutputImageType
]
gradientfilter = FilterType.New()
gradientfilter.SetInput(castfilter.GetOutput())
gradientfilter.SetNumberOfIterations(args.number_of_iterations)
gradientfilter.SetTimeStep(0.125)
gradientfilter.SetConductanceParameter(args.conductance)

WriterType = itk.ImageFileWriter[OutputImageType]
writer = WriterType.New()
writer.SetFileName(args.output_image)
writer.SetInput(gradientfilter.GetOutput())

writer.Update()
