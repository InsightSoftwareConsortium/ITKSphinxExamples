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
#include "itkPointSet.h"
#include "itkBoundingBox.h"

int main(int, char*[])
{
  typedef float CoordType;
  const unsigned int Dimension = 3;

  typedef itk::PointSet< CoordType, Dimension >   PointSetType;

  typedef PointSetType::PointIdentifier         PointIdentifier;
  typedef PointSetType::PointType               PointType;
  typedef PointSetType::PointsContainerPointer  PointsContainerPointer;

  PointSetType::Pointer   pointSet = PointSetType::New();
  PointsContainerPointer  points = pointSet->GetPoints();

  // Create points
  PointType p0, p1, p2;

  p0[0]=  0.0; p0[1]= 0.0; p0[2]= 0.0;
  p1[0]=  0.1; p1[1]= 0.0; p1[2]= 0.0;
  p2[0]=  0.0; p2[1]= 0.1; p2[2]= 0.0;

  points->InsertElement(0, p0);
  points->InsertElement(1, p1);
  points->InsertElement(2, p2);

  typedef itk::BoundingBox< PointIdentifier, Dimension, CoordType >
    BoundingBoxType;

  BoundingBoxType::Pointer boundingBox = BoundingBoxType::New();
  boundingBox->SetPoints(points);
  boundingBox->ComputeBoundingBox();

  std::cout << "bounds: " << boundingBox->GetBounds() << std::endl;
  std::cout << "center: " << boundingBox->GetCenter() << std::endl;
  std::cout << "diagonal length squared: "
            << boundingBox->GetDiagonalLength2() << std::endl;

  return EXIT_SUCCESS;
}
