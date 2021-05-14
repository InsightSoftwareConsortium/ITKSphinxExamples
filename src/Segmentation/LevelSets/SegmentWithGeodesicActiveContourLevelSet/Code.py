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

import sys
import itk

if len(sys.argv) != 11:
    print(
        "Usage: " + sys.argv[0] + "<InputFileName>  <OutputFileName>"
        " <seedX> <seedY> <InitialDistance> <Sigma> <SigmoidAlpha> "
        "<SigmoidBeta> <PropagationScaling> <NumberOfIterations>"
    )
    sys.exit(1)

input_filename = sys.argv[1]
output_filename = sys.argv[2]

seed_pos_x = int(sys.argv[3])
seed_pos_y = int(sys.argv[4])

initial_distance = float(sys.argv[5])
sigma = float(sys.argv[6])
alpha = float(sys.argv[7])
beta = float(sys.argv[8])
propagation_scaling = float(sys.argv[9])
number_of_iterations = int(sys.argv[10])
seed_value = -initial_distance

InputPixelType = itk.ctype("float")
input_image = itk.imread(input_filename, InputPixelType)

Dimension = input_image.GetImageDimension()

smoothed = itk.curvature_anisotropic_diffusion_image_filter(
    input_image, time_step=0.125, number_of_iterations=5, conductance_parameter=9.0
)

gradient_magnitude = itk.gradient_magnitude_recursive_gaussian_image_filter(
    smoothed, sigma=sigma
)

sigmoid = itk.sigmoid_image_filter(
    gradient_magnitude, output_minimum=0.0, output_maximum=1.0, alpha=alpha, beta=beta
)

Dimension = input_image.GetImageDimension()
seeds = itk.VectorContainer[itk.UI, itk.LevelSetNode[InputPixelType, Dimension]].New()
seeds.Initialize()

seed_position = itk.Index[Dimension]()
seed_position[0] = seed_pos_x
seed_position[1] = seed_pos_y
node = itk.LevelSetNode[InputPixelType, Dimension]()
node.SetValue(-5.0)
node.SetIndex(seed_position)
seeds.InsertElement(0, node)

fast_marching = itk.fast_marching_image_filter(
    trial_points=seeds,
    speed_constant=1.0,
    output_size=input_image.GetBufferedRegion().GetSize(),
)

geodesic_active_contour = itk.geodesic_active_contour_level_set_image_filter(
    fast_marching,
    propagation_scaling=propagation_scaling,
    curvature_scaling=1.0,
    advection_scaling=1.0,
    maximum_r_m_s_error=0.02,
    number_of_iterations=number_of_iterations,
    feature_image=sigmoid,
)


OutputPixelType = itk.ctype("unsigned char")
OutputImageType = itk.Image[OutputPixelType, Dimension]
thresholded = itk.binary_threshold_image_filter(
    geodesic_active_contour,
    lower_threshold=-1000.0,
    upper_threshold=0.0,
    outside_value=itk.NumericTraits[OutputPixelType].min(),
    inside_value=itk.NumericTraits[OutputPixelType].max(),
    ttype=[type(geodesic_active_contour), OutputImageType],
)

itk.imwrite(thresholded, output_filename)

smoothed_cast = itk.rescale_intensity_image_filter(
    smoothed, ttype=(type(smoothed), OutputImageType)
)
itk.imwrite(smoothed_cast, "GeodesicActiveContourImageFilterOutput1.png")

gradient_magnitude_cast = itk.rescale_intensity_image_filter(
    smoothed, ttype=(type(gradient_magnitude), OutputImageType)
)
itk.imwrite(gradient_magnitude_cast, "GeodesicActiveContourImageFilterOutput2.png")

sigmoid_cast = itk.rescale_intensity_image_filter(
    sigmoid, ttype=(type(sigmoid), OutputImageType)
)
itk.imwrite(sigmoid_cast, "GeodesicActiveContourImageFilterOutput3.png")

fast_marching_cast = itk.rescale_intensity_image_filter(
    fast_marching, ttype=(type(fast_marching), OutputImageType)
)
itk.imwrite(fast_marching_cast, "GeodesicActiveContourImageFilterOutput4.png")
