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
#include "itkVector.h"
#include "itkListSample.h"
#include "itkWeightedCentroidKdTreeGenerator.h"
#include "itkEuclideanDistanceMetric.h"

int
main()
{
  using MeasurementVectorType = itk::Vector<float, 2>;

  using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;
  auto sample = SampleType::New();
  sample->SetMeasurementVectorSize(2);

  MeasurementVectorType mv;
  for (unsigned int i = 0; i < 100; ++i)
  {
    mv[0] = static_cast<float>(i);
    mv[1] = static_cast<float>(i);
    sample->PushBack(mv);
  }

  using TreeGeneratorType = itk::Statistics::KdTreeGenerator<SampleType>;
  auto treeGenerator = TreeGeneratorType::New();
  treeGenerator->SetSample(sample);
  treeGenerator->SetBucketSize(16);
  treeGenerator->Update();

  using TreeType = TreeGeneratorType::KdTreeType;

  TreeType::Pointer tree = treeGenerator->GetOutput();

  MeasurementVectorType queryPoint;
  queryPoint[0] = 10.0;
  queryPoint[1] = 7.0;

  // K-Neighbor search
  std::cout << "K-Neighbor search:" << std::endl;
  unsigned int                           numberOfNeighbors = 3;
  TreeType::InstanceIdentifierVectorType neighbors;
  tree->Search(queryPoint, numberOfNeighbors, neighbors);

  for (unsigned long neighbor : neighbors)
  {
    std::cout << tree->GetMeasurementVector(neighbor) << std::endl;
  }

  // Radius search
  std::cout << "Radius search:" << std::endl;
  double radius = 4.0;
  tree->Search(queryPoint, radius, neighbors);
  std::cout << "There are " << neighbors.size() << " neighbors." << std::endl;
  for (unsigned long neighbor : neighbors)
  {
    std::cout << tree->GetMeasurementVector(neighbor) << std::endl;
  }

  return EXIT_SUCCESS;
}
