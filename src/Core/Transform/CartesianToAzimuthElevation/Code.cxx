/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include "itkPoint.h"
#include "itkAzimuthElevationToCartesianTransform.h"

int main(int, char*[])
{
    using PointType = itk::Point<double, 3>;
    PointType spherical;
    spherical[0] = 0.0;
    spherical[1] = 45; // set elevation to 45 degrees
    spherical[2] = 1;
    std::cout << "spherical: " << spherical << std::endl;

    using AzimuthElevationToCartesian = itk::AzimuthElevationToCartesianTransform< double, 3 >;
    AzimuthElevationToCartesian::Pointer azimuthElevation =
            AzimuthElevationToCartesian::New();

    std::cout << "Cartesian: " << azimuthElevation->TransformAzElToCartesian(spherical) << std::endl;

    return EXIT_SUCCESS;
}

