/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#include "itkBlobSpatialObject.h"

int
main(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  using BlobType = itk::BlobSpatialObject<2>;

  // Create a list of points
  BlobType::BlobPointListType points;
  for (unsigned int i = 0; i < 20; i++)
  {
    BlobType::BlobPointType point;
    point.SetPositionInObjectSpace(i, i);

    points.push_back(point);
  }

  BlobType::Pointer blob = BlobType::New();
  blob->SetPoints(points);

  BlobType::BoundingBoxType::BoundsArrayType bounds = blob->GetMyBoundingBoxInWorldSpace()->GetBounds();
  std::cout << "Bounds: " << bounds << std::endl;

  return EXIT_SUCCESS;
}
