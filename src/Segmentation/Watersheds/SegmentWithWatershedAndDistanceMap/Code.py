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

# Run with:
# ./Code.py <input_image_filename> <reversed_input_output_filename>
# <distance_map_output_filename> <watershed_output_filename>
# <segmentation_result_output_filename> <binarizing_radius>
# <majority_threshold> <watershed_threshold> <level>
# e.g.
# ./Code.py PlateauBorder.tif
# reversedInputImage.tif distanceMap.tif watershed.tif segmentationResult.tif
# 2 2 0.01 0.5 3
# (A rule of thumb is to set the Threshold to be about 1 / 100 of the Level.)
#
#  threshold: absolute minimum height value used during processing.
#        Raising this threshold percentage effectively decreases the number of local minima in the input,
#        resulting in an initial segmentation with fewer regions.
#        The assumption is that the shallow regions that thresholding removes are of of less interest.
#  level: controls the depth of metaphorical flooding of the image.
#        That is, it sets the maximum saliency value of interest in the result.
#        Raising and lowering the Level influences the number of segments
#        in the basic segmentation that are merged to produce the final output.
#        A level of 1.0 is analogous to flooding the image up to a
#        depth that is 100 percent of the maximum value in the image.
#        A level of 0.0 produces the basic segmentation, which will typically be very oversegmented.
#        Level values of interest are typically low (i.e. less than about 0.40 or 40%),
#        since higher values quickly start to undersegment the image.


import argparse

import itk
import numpy as np

parser = argparse.ArgumentParser(
    description="Segment an image using the watershed method and the signed Maurer distance map."
)
parser.add_argument("input_image_filename")
parser.add_argument("reversed_input_output_filename")
parser.add_argument("distance_map_output_filename")
parser.add_argument("watershed_output_filename")
parser.add_argument("segmentation_result_output_filename")
parser.add_argument("binarizing_radius", type=int)
parser.add_argument("majority_threshold", type=int)
parser.add_argument("watershed_threshold", type=float)
parser.add_argument("level", type=float)
parser.add_argument("cleaning_structuring_element_radius", type=int)
args = parser.parse_args()

dimension = 3

uchar_pixel_type = itk.UC
uchar_image_type = itk.Image[uchar_pixel_type, dimension]

float_pixel_type = itk.F
float_image_type = itk.Image[float_pixel_type, dimension]

rgb_pixel_type = itk.RGBPixel[uchar_pixel_type]
RGBImageType = itk.Image[rgb_pixel_type, dimension]

stack_image = itk.imread(args.input_image_filename)

# Create bubble image: get a binarized version of the input image
index_radius = itk.Size[dimension]()
index_radius.Fill(args.binarizing_radius)

bubble_image = itk.voting_binary_iterative_hole_filling_image_filter(
    stack_image,
    radius=index_radius,
    background_value=0,
    foreground_value=255,
    majority_threshold=args.majority_threshold,
)

# Write bubble image
itk.imwrite(bubble_image, args.reversed_input_output_filename)

# Watershed on bubbles
bbl_cast_image = itk.cast_image_filter(bubble_image, ttype=(uchar_image_type, float_image_type))

# Normalize the image to the [0, 255] range
bubble_image_preclamp = itk.multiply_image_filter(bbl_cast_image, constant=255.0)

bubble_image_clamp = itk.clamp_image_filter(bubble_image_preclamp, bounds=(0, 255))

# Get the distance map of the input image
distance_map_image = itk.signed_maurer_distance_map_image_filter(
    bubble_image_clamp, inside_is_positive=False
)

itk.imwrite(distance_map_image, args.distance_map_output_filename)

# Apply the watershed segmentation
watershed_image = itk.watershed_image_filter(
    distance_map_image, threshold=args.watershed_threshold, level=args.level,
)

# distance_map_array = itk.array_view_from_image(distance_map_image)
# watershed_array = itk.array_view_from_image(watershed_image)

# Cast to unsigned char so that it can be written as a TIFF image
# WatershedImageFilter produces itk.ULL, but CastImageFilter does not wrap
# itk.ULL: see ITK issue 2551
# ws_cast_image = itk.cast_image_filter(watershed_image, ttype=(watershed_image.__class__, uchar_image_type))
# Workaround
rgb_ws_image = itk.scalar_to_rgb_colormap_image_filter(watershed_image, colormap=itk.ScalarToRGBColormapImageFilterEnums.RGBColormapFilter_Jet)

# itk.imwrite(ws_cast_image, args.watershed_output_filename)
itk.imwrite(rgb_ws_image, args.watershed_output_filename)

# Clean the segmentation image: remove small objects by performing an
# opening morphological operation
structuring_element_type = itk.FlatStructuringElement[dimension]
structuring_element = structuring_element_type.Ball(args.cleaning_structuring_element_radius)

segmented_clean_image = itk.binary_morphological_opening_image_filter(watershed_image, kernel=structuring_element)

itk.imwrite(segmented_clean_image, args.segmentation_result_output_filename)
