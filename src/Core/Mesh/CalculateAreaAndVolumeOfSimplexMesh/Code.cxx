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
#define _USE_MATH_DEFINES // needed for Visual Studio (before #include <cmath>)
#include <itkSimplexMesh.h>
#include <itkRegularSphereMeshSource.h>
#include <itkTriangleMeshToSimplexMeshFilter.h>
#include <itkSimplexMeshVolumeCalculator.h>

using TMesh = itk::Mesh<float, 3>;
using TSimplex = itk::SimplexMesh<float, 3>;
using TSphere = itk::RegularSphereMeshSource<TMesh>;
using TConvert = itk::TriangleMeshToSimplexMeshFilter<TMesh, TSimplex>;
using TVolume = itk::SimplexMeshVolumeCalculator<TSimplex>;

int
main(int, char *[])
{

  // Create a spherical mesh with known radius and resolution.
  TSphere::Pointer    source = TSphere::New();
  TSphere::VectorType scale;
  scale.Fill(5.0);
  source->SetScale(scale);
  source->SetResolution(5);
  source->Update();

  // Ensure that all cells of the mesh are triangles.
  for (TMesh::CellsContainerIterator it = source->GetOutput()->GetCells()->Begin();
       it != source->GetOutput()->GetCells()->End();
       ++it)
  {
    TMesh::CellAutoPointer cell;
    source->GetOutput()->GetCell(it->Index(), cell);
    if (3 != cell->GetNumberOfPoints())
    {
      std::cerr << "ERROR: All cells must be trianglar." << std::endl;
      return EXIT_FAILURE;
    }
  }

  // Convert the triangle mesh to a simplex mesh.
  TConvert::Pointer convert = TConvert::New();
  convert->SetInput(source->GetOutput());
  convert->Update();

  // Calculate the volume and area of the simplex mesh.
  TVolume::Pointer volume = TVolume::New();
  volume->SetSimplexMesh(convert->GetOutput());
  volume->Compute();

  // Compare with the volume and area of an ideal sphere.
  std::cout << "Ideal Volume: " << 4.0 / 3.0 * M_PI * pow(5.0, 3) << std::endl;
  std::cout << "Mesh Volume: " << volume->GetVolume() << std::endl;
  std::cout << "Ideal Surface Area: " << 4.0 * M_PI * pow(5.0, 2) << std::endl;
  std::cout << "Mesh Surface Area: " << volume->GetArea() << std::endl;

  return EXIT_SUCCESS;
}
