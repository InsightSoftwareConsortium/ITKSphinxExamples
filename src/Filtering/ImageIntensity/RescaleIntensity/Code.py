#!/usr/bin/env python

import sys
import itk

if len(sys.argv) != 5:
    print(
        "Usage: "
        + sys.argv[0]
        + " <InputFileName> <OutputFileName> <OutputMin> <OutputMax>"
    )
    sys.exit(1)

input_image = sys.argv[1]
output_image = sys.argv[1]
output_minimum = int(sys.argv[3])
output_maximum = int(sys.argv[4])

image = itk.imread(sys.argv[1])

image = itk.rescale_intensity_image_filter(
    image, output_minimum=output_minimum, output_maximum=output_maximum
)

itk.imwrite(image, sys.argv[2])
