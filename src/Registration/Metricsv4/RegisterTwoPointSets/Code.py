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

# Adapted from ITK itkJensenHavrdaCharvatTsallisPointSetMetricRegistrationTest.cxx

import sys
from math import pi, sin, cos

import itk


# Generate two circles with a small offset
def make_circles(l_dimension: int = 2):
    PointSetType = itk.PointSet[itk.F, l_dimension]

    RADIUS = 100
    offset = [2.0] * l_dimension

    fixed_points = PointSetType.New()
    moving_points = PointSetType.New()
    fixed_points.Initialize()
    moving_points.Initialize()

    step = 0.1
    for count in range(0, int(2 * pi / step) + 1):

        theta = count * step

        fixed_point = list()
        fixed_point.append(RADIUS * cos(theta))
        for dim in range(1, l_dimension):
            fixed_point.append(RADIUS * sin(theta))
        fixed_points.SetPoint(count, fixed_point)

        moving_point = [fixed_point[dim] + offset[dim] for dim in range(0, l_dimension)]
        moving_points.SetPoint(count, moving_point)

    return fixed_points, moving_points


def test_registration(l_dimension: int = 2):
    # Define test parameters

    num_iterations = 10

    passed = True
    tolerance = 0.05

    # Define types
    PointSetType = itk.PointSet[itk.F, l_dimension]
    AffineTransformType = itk.AffineTransform[itk.D, l_dimension]
    PointSetMetricType = itk.JensenHavrdaCharvatTsallisPointSetToPointSetMetricv4[
        PointSetType
    ]
    ShiftScalesType = itk.RegistrationParameterScalesFromPhysicalShift[
        PointSetMetricType
    ]
    OptimizerType = itk.RegularStepGradientDescentOptimizerv4[itk.D]

    # Make point sets
    fixed_set, moving_set = make_circles(l_dimension)

    transform = AffineTransformType.New()
    transform.SetIdentity()

    metric = PointSetMetricType.New(
        FixedPointSet=fixed_set,
        MovingPointSet=moving_set,
        PointSetSigma=1.0,
        KernelSigma=10.0,
        UseAnisotropicCovariances=False,
        CovarianceKNeighborhood=5,
        EvaluationKNeighborhood=10,
        MovingTransform=transform,
        Alpha=1.1,
    )
    metric.Initialize()

    shift_scale_estimator = ShiftScalesType.New(
        Metric=metric, VirtualDomainPointSet=metric.GetVirtualTransformedPointSet()
    )

    optimizer = OptimizerType.New(
        Metric=metric,
        NumberOfIterations=num_iterations,
        ScalesEstimator=shift_scale_estimator,
        MaximumStepSizeInPhysicalUnits=3.0,
        MinimumConvergenceValue=0.0,
        ConvergenceWindowSize=10,
    )

    def print_iteration():
        print(
            f"It: {optimizer.GetCurrentIteration()}"
            f" metric value: {optimizer.GetCurrentMetricValue():.6f} "
        )

    optimizer.AddObserver(itk.IterationEvent(), print_iteration)

    # Run optimization to align the point sets
    optimizer.StartOptimization()

    print(f"Number of iterations: {num_iterations}")
    print(f"Moving-source final value: {optimizer.GetCurrentMetricValue()}")
    print(f"Moving-source final position: {list(optimizer.GetCurrentPosition())}")
    print(f"Optimizer scales: {list(optimizer.GetScales())}")
    print(f"Optimizer learning rate: {optimizer.GetLearningRate()}")

    # applying the resultant transform to moving points and verify result
    print("Fixed\tMoving\tMovingTransformed\tFixedTransformed\tDiff")

    moving_inverse = metric.GetMovingTransform().GetInverseTransform()
    fixed_inverse = metric.GetFixedTransform().GetInverseTransform()

    def print_point(vals: list) -> str:
        return f'[{",".join(f"{x:.4f}" for x in vals)}]'

    for n in range(0, metric.GetNumberOfComponents()):
        transformed_moving_point = moving_inverse.TransformPoint(moving_set.GetPoint(n))
        transformed_fixed_point = fixed_inverse.TransformPoint(fixed_set.GetPoint(n))

        difference = [
            transformed_moving_point[dim] - transformed_fixed_point[dim]
            for dim in range(0, l_dimension)
        ]

        print(
            f"{print_point(fixed_set.GetPoint(n))}"
            f"\t{print_point(moving_set.GetPoint(n))}"
            f"\t{print_point(transformed_moving_point)}"
            f"\t{print_point(transformed_fixed_point)}"
            f"\t{print_point(difference)}"
        )

        if any(abs(difference[dim]) > tolerance for dim in range(0, l_dimension)):
            passed = False

    if not passed:
        raise Exception("Transform outside of allowable tolerance")
    else:
        print("Transform is within allowable tolerance.")


if __name__ == "__main__":
    if len(sys.argv) == 2:
        dimension = int(sys.argv[1])
        test_registration(dimension)
    else:
        test_registration()
