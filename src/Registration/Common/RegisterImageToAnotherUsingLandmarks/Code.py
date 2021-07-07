#!/usr/bin/env python3

# =========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
# =========================================================================*/

import itk

Dimension = 2
PixelType = itk.ctype("unsigned char")
ImageType = itk.Image[PixelType, Dimension]


def create_fixed_image():
    start = [
        0,
    ] * Dimension
    size = [
        100,
    ] * Dimension

    region = itk.ImageRegion[Dimension](start, size)

    ImageType = itk.Image[PixelType, Dimension]
    image = ImageType.New()
    image.SetRegions(region)
    image.Allocate()
    image.FillBuffer(0)

    image[11:20, 11:20] = 255

    itk.imwrite(image, "fixedPython.png")

    return image


def create_moving_image():
    start = [
        0,
    ] * Dimension
    size = [
        100,
    ] * Dimension

    region = itk.ImageRegion[Dimension](start, size)

    ImageType = itk.Image[PixelType, Dimension]
    image = ImageType.New()
    image.SetRegions(region)
    image.Allocate()
    image.FillBuffer(0)

    image[51:60, 51:60] = 100

    itk.imwrite(image, "movingPython.png")

    return image


fixed_image = create_fixed_image()
moving_image = create_moving_image()

LandmarkPointType = itk.Point[itk.D, Dimension]
LandmarkContainerType = itk.vector[LandmarkPointType]

fixed_landmarks = LandmarkContainerType()
moving_landmarks = LandmarkContainerType()

fixed_point = LandmarkPointType()
moving_point = LandmarkPointType()

fixed_point[0] = 10
fixed_point[1] = 10
moving_point[0] = 50
moving_point[1] = 50
fixed_landmarks.push_back(fixed_point)
moving_landmarks.push_back(moving_point)

fixed_point[0] = 20
fixed_point[1] = 10
moving_point[0] = 60
moving_point[1] = 50
fixed_landmarks.push_back(fixed_point)
moving_landmarks.push_back(moving_point)

fixed_point[0] = 20
fixed_point[1] = 20
moving_point[0] = 60
moving_point[1] = 60
fixed_landmarks.push_back(fixed_point)
moving_landmarks.push_back(moving_point)

TransformInitializerType = itk.LandmarkBasedTransformInitializer[
    itk.Transform[itk.D, Dimension, Dimension]
]
transform_initializer = TransformInitializerType.New()

transform_initializer.SetFixedLandmarks(fixed_landmarks)
transform_initializer.SetMovingLandmarks(moving_landmarks)

transform = itk.Rigid2DTransform[itk.D].New()
transform_initializer.SetTransform(transform)
transform_initializer.InitializeTransform()

output = itk.resample_image_filter(
    moving_image,
    transform=transform,
    use_reference_image=True,
    reference_image=fixed_image,
    default_pixel_value=200,
)

itk.imwrite(output, "outputPython.png")
