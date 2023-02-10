#!/usr/bin/env python

# ==========================================================================
#
#   Copyright Insight Software Consortium
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
# ==========================================================================*/

import itk
import numpy as np
import argparse

parser = argparse.ArgumentParser(description="Extract an isosurface.")
parser.add_argument("input_image")
parser.add_argument("output_mesh")
parser.add_argument("lower_threshold", type=int)
parser.add_argument("upper_threshold", type=int)
args = parser.parse_args()

input_image = itk.imread(args.input_image)

thresholded = itk.binary_threshold_image_filter(
    input_image,
    lower_threshold=args.lower_threshold,
    upper_threshold=args.upper_threshold,
    outside_value=0,
    inside_value=255,
)

output_mesh = itk.binary_mask3_d_mesh_source(thresholded, object_value=255)

itk.meshwrite(output_mesh, args.output_mesh)
