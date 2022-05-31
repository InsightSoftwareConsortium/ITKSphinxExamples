#!/usr/bin/env python

# ==========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License")
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
# ==========================================================================

import itk
import argparse

parser = argparse.ArgumentParser(
    description="Adaptive Histogram Equalization Image Filter."
)
parser.add_argument("input_image")
parser.add_argument("output_image")
parser.add_argument("alpha", type=float)
parser.add_argument("beta", type=float)
parser.add_argument("radius", type=int)
args = parser.parse_args()

Dimension = 2

PixelType = itk.ctype("unsigned char")
ImageType = itk.Image[PixelType, Dimension]

reader = itk.ImageFileReader[ImageType].New()
reader.SetFileName(args.input_image)

histogramEqualization = itk.AdaptiveHistogramEqualizationImageFilter.New(reader)
histogramEqualization.SetAlpha(args.alpha)
histogramEqualization.SetBeta(args.beta)

radius = itk.Size[Dimension]()
radius.Fill(args.radius)
histogramEqualization.SetRadius(radius)

itk.imwrite(histogramEqualization, args.output_image)
