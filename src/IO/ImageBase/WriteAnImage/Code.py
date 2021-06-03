#!/usr/bin/env python

import sys
import itk

if len(sys.argv) > 1:
    output_filename = sys.argv[1]
else:
    output_filename = "testPython.png"

pixel_type = itk.UC
dimension = 2
image_type = itk.Image[pixel_type, dimension]

start = itk.Index[dimension]()
start.Fill(0)

size = itk.Size[dimension]()
size[0] = 200
size[1] = 300

region = itk.ImageRegion[dimension]()
region.SetIndex(start)
region.SetSize(size)

image = image_type.New(Regions=region)
image.Allocate()

itk.imwrite(image, output_filename)
