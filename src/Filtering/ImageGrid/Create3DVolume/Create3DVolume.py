#!/usr/bin/env python

import sys
import itk

if len(sys.argv) < 3:
    print("Usage: " + sys.argv[0] + " <input1> <input2> <input3> ... <output>")
    sys.exit(1)

InputDimension = 2
OutputDimension = 3

PixelType = itk.UC

InputImageType = itk.Image[PixelType, InputDimension]
OutputImageType = itk.Image[PixelType, OutputDimension]

reader = itk.ImageFileReader[InputImageType].New()

tileFilter = itk.TileImageFilter[InputImageType, OutputImageType].New()

layout = [2, 2, 0]
tileFilter.SetLayout(layout)

for ii in range(1, len(argv)-1):
    reader.SetFileName(sys.argv[ii])
    reader.Update()

    inputImage = reader.GetOutput()
    inputImage.DisconnectPipeline()

    tileFilter.SetInput(ii
