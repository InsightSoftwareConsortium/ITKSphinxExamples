#!/usr/bin/env python
#=========================================================================
#
#  Copyright NumFOCUS
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#

# Python example demonstrating itk.ExhaustiveOptimizer usage
import sys
from math import pi

import itk

EXIT_SUCCESS = 0
EXIT_FAILURE = 1

def main(argv):
    if len(argv) < 3:
        raise Exception(f'Usage: {argv[0]} fixed_image moving_image')
    
    fixed_image = itk.imread(argv[1], itk.F)
    moving_image = itk.imread(argv[2],itk.F)
    
    dimension = fixed_image.GetImageDimension()
    FixedImageType = type(fixed_image)
    MovingImageType = type(moving_image)

    if dimension == 2:
        transform = itk.Euler2DTransform[itk.D].New()
    else:
        raise Exception(f'Unsupported dimension: {dimension}')
    
    TransformInitializerType = \
        itk.CenteredTransformInitializer[itk.MatrixOffsetTransformBase[itk.D,
                                                                       dimension,
                                                                       dimension],
                                         FixedImageType, MovingImageType]
    initializer = TransformInitializerType.New(Transform=transform,
        FixedImage=fixed_image,
        MovingImage=moving_image,)
    initializer.InitializeTransform()
    
    metric = itk.MeanSquaresImageToImageMetricv4[FixedImageType, MovingImageType].New()
    
    optimizer = itk.ExhaustiveOptimizerv4[itk.D].New()
    def print_iteration():
        print(f'Iteration:'
              f'{optimizer.GetCurrentIteration()}\t'
              f'{list(optimizer.GetCurrentIndex())} \t'
              f'{optimizer.GetCurrentValue():10.4f}\t'
              f'{list(optimizer.GetCurrentPosition())}\t')
    
    optimizer.AddObserver(itk.IterationEvent(), print_iteration)

    angles = 12
    optimizer.SetNumberOfSteps([int(angles / 2),0,0])

    # Initialize scales and set back to optimizer
    scales = optimizer.GetScales()
    scales.SetSize(3)
    scales.SetElement(0, 2.0 * pi / angles)
    scales.SetElement(1, 1.0)
    scales.SetElement(2, 1.0)
    optimizer.SetScales(scales)
    
    RegistrationType = itk.ImageRegistrationMethodv4[FixedImageType,MovingImageType]
    registration = RegistrationType.New(Metric=metric,
        Optimizer=optimizer,
        FixedImage=fixed_image,
        MovingImage=moving_image,
        InitialTransform=transform,
        NumberOfLevels=1)

    try:
        registration.Update()

        print(f'MinimumMetricValue: {optimizer.GetMinimumMetricValue():.4f}\t'
              f'MaximumMetricValue: {optimizer.GetMaximumMetricValue():.4f}\n'
              f'MinimumMetricValuePosition: {list(optimizer.GetMinimumMetricValuePosition())}\t'
              f'MaximumMetricValuePosition: {list(optimizer.GetMaximumMetricValuePosition())}\n'
              f'StopConditionDescription: {optimizer.GetStopConditionDescription()}\t')

    except Exception as e:
        print(f'Exception caught: {e}')
        return EXIT_FAILURE

    return EXIT_SUCCESS

if __name__ == "__main__":
    main(sys.argv)
