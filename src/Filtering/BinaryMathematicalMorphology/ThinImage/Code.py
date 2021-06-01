#!/usr/bin/env python

import sys
import itk

PixelType = itk.UC
Dimension = 2
ImageType = itk.Image[PixelType, Dimension]

if len(sys.argv) == 2:
    image = itk.imread(sys.argv[1])

else:
    # Create an image
    start = itk.Index[Dimension]()
    start.Fill(0)

    size = itk.Size[Dimension]()
    size.Fill(100)

    region = itk.ImageRegion[Dimension]()
    region.SetIndex(start)
    region.SetSize(size)

    image = ImageType.New(Regions=region)
    image.Allocate()
    image.FillBuffer(0)

    # Draw a 5 pixel wide line
    image[50:55, 20:80] = 255

    # Write Image
    itk.imwrite(image, "input.png")

image = itk.binary_thinning_image_filter(image)

# Rescale the image so that it can be seen (the output is 0 and 1, we want 0 and 255)
image = itk.rescale_intensity_image_filter(image, output_minimum=0, output_maximum=255)

# Write Image
itk.imwrite(image, "outputPython.png")
