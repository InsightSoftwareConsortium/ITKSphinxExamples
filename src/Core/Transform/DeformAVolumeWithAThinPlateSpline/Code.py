#!/usr/bin/env python

# Copyright NumFOCUS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#        https://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import itk
import numpy as np

parser = argparse.ArgumentParser(
    description="Deform a Volume With a Thin Plate Spline."
)
parser.add_argument("source_landmarks")
parser.add_argument("target_landmarks")
parser.add_argument("input_image")
parser.add_argument("deformed_image")
parser.add_argument("checker_board_image")
args = parser.parse_args()

Dimension = 3
thin_plate_spline = itk.ThinPlateSplineKernelTransform[itk.D, Dimension].New()

source_landmarks_mesh = itk.meshread(args.source_landmarks)
# Cast points from float32 to float64
points = itk.array_from_vector_container(source_landmarks_mesh.GetPoints())
points = points.astype(np.float64)
source_landmarks = thin_plate_spline.GetSourceLandmarks()
source_landmarks.SetPoints(itk.vector_container_from_array(points.flatten()))

target_landmarks_mesh = itk.meshread(args.target_landmarks)
# Cast points from float32 to float64
points = itk.array_from_vector_container(target_landmarks_mesh.GetPoints())
points = points.astype(np.float64)
target_landmarks = thin_plate_spline.GetTargetLandmarks()
target_landmarks.SetPoints(itk.vector_container_from_array(points.flatten()))

thin_plate_spline.ComputeWMatrix()

input_image = itk.imread(args.input_image)

deformed_image = itk.resample_image_filter(
    input_image,
    use_reference_image=True,
    reference_image=input_image,
    transform=thin_plate_spline,
)
itk.imwrite(deformed_image, args.deformed_image)

checker_board = itk.checker_board_image_filter(input_image, deformed_image)
itk.imwrite(checker_board, args.checker_board_image)
