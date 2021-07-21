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
#include "itkVoronoiDiagram2DGenerator.h"
#include "itkImageFileWriter.h"
#include "itkVTKPolyDataWriter.h"

int
main(int, char *[])
{
  constexpr double height = 100;
  constexpr double width = 100;

  using VoronoiDiagramType = itk::VoronoiDiagram2D<double>;
  using VoronoiGeneratorType = itk::VoronoiDiagram2DGenerator<double>;

  using PointType = VoronoiDiagramType::PointType;
  using CellType = VoronoiDiagramType::CellType;
  using CellAutoPointer = VoronoiDiagramType::CellAutoPointer;
  using PointIdIterator = CellType::PointIdIterator;
  using NeighborIdIterator = VoronoiDiagramType::NeighborIdIterator;

  VoronoiDiagramType::Pointer   voronoiDiagram = VoronoiDiagramType::New();
  VoronoiGeneratorType::Pointer voronoiGenerator = VoronoiGeneratorType::New();

  PointType insize;
  insize[0] = width;
  insize[1] = height;
  voronoiGenerator->SetBoundary(insize);

  // Create a list of seeds
  std::vector<PointType> seeds;
  PointType              seed0;
  seed0[0] = 50;
  seed0[1] = 50;
  seeds.push_back(seed0);

  PointType seed1;
  seed1[0] = 25;
  seed1[1] = 25;
  seeds.push_back(seed1);

  PointType seed2;
  seed2[0] = 75;
  seed2[1] = 25;
  seeds.push_back(seed2);

  PointType seed3;
  seed3[0] = 25;
  seed3[1] = 75;
  seeds.push_back(seed3);

  PointType seed4;
  seed4[0] = 75;
  seed4[1] = 75;
  seeds.push_back(seed4);

  for (const auto & seed : seeds)
  {
    voronoiGenerator->AddOneSeed(seed);
  }

  voronoiGenerator->Update();
  voronoiDiagram = voronoiGenerator->GetOutput();

  for (unsigned int i = 0; i < seeds.size(); i++)
  {
    PointType currP = voronoiDiagram->GetSeed(i);
    std::cout << "Seed No." << i << ": At (" << currP[0] << "," << currP[1] << ")" << std::endl;
    std::cout << "  Boundary Vertices List (in order):";
    CellAutoPointer currCell;
    voronoiDiagram->GetCellId(i, currCell);
    PointIdIterator currCellP;
    for (currCellP = currCell->PointIdsBegin(); currCellP != currCell->PointIdsEnd(); ++currCellP)
    {
      std::cout << (*currCellP) << ",";
    }
    std::cout << std::endl;
    std::cout << "  Neighbors (Seed No.):";
    NeighborIdIterator currNeibor;
    for (currNeibor = voronoiDiagram->NeighborIdsBegin(i); currNeibor != voronoiDiagram->NeighborIdsEnd(i);
         ++currNeibor)
    {
      std::cout << (*currNeibor) << ",";
    }
    std::cout << std::endl << std::endl;
  }

  std::cout << "Vertices Informations:" << std::endl;
  VoronoiDiagramType::VertexIterator allVerts;
  int                                j = 0;
  for (allVerts = voronoiDiagram->VertexBegin(); allVerts != voronoiDiagram->VertexEnd(); ++allVerts)
  {
    std::cout << "Vertices No." << j;
    j++;
#if ITK_VERSION_MAJOR < 4
    std::cout << ": At (" << (*allVerts)[0] << "," << (*allVerts)[1] << ")" << std::endl;
#else
    std::cout << ": At (" << (allVerts.Value())[0] << "," << (allVerts.Value())[1] << ")" << std::endl;
#endif
  }

  // Write the resulting mesh
  using WriterType = itk::VTKPolyDataWriter<VoronoiDiagramType::Superclass>;
  WriterType::Pointer vtkPolyDataWriter = WriterType::New();
  vtkPolyDataWriter->SetInput(voronoiDiagram);
  vtkPolyDataWriter->SetFileName("voronoi.vtk");
  vtkPolyDataWriter->Update();

  // Setup an image to visualize the input
  {
    using ImageType = itk::Image<unsigned char, 2>;

    ImageType::IndexType start;
    start.Fill(0);

    ImageType::SizeType size;
    size.Fill(100);

    ImageType::RegionType region(start, size);

    ImageType::Pointer image = ImageType::New();
    image->SetRegions(region);
    image->Allocate();
    image->FillBuffer(0);

    ImageType::IndexType ind;
    ind[0] = 50;
    ind[1] = 50;
    image->SetPixel(ind, 255);

    ind[0] = 25;
    ind[1] = 25;
    image->SetPixel(ind, 255);

    ind[0] = 75;
    ind[1] = 25;
    image->SetPixel(ind, 255);

    ind[0] = 25;
    ind[1] = 75;
    image->SetPixel(ind, 255);

    ind[0] = 75;
    ind[1] = 75;
    image->SetPixel(ind, 255);

    itk::WriteImage(image, "image.png");
  }

  return EXIT_SUCCESS;
}
