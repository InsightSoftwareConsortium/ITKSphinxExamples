/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkMesh.h"
#include "itkLineCell.h"

int
main(int, char *[])
{
  using PixelType = float;
  using MeshType = itk::Mesh<PixelType, 2>;

  using CellType = MeshType::CellType;
  using LineType = itk::LineCell<CellType>;

  auto mesh = MeshType::New();

  using PointType = MeshType::PointType;
  PointType point;

  const unsigned int numberOfPoints = 10;
  for (unsigned int id = 0; id < numberOfPoints; id++)
  {
    point[0] = static_cast<PointType::ValueType>(id);              // x
    point[1] = std::log(static_cast<double>(id) + itk::Math::eps); // y
    mesh->SetPoint(id, point);
  }

  CellType::CellAutoPointer line;
  const unsigned int        numberOfCells = numberOfPoints - 1;
  for (unsigned int cellId = 0; cellId < numberOfCells; cellId++)
  {
    line.TakeOwnership(new LineType);
    line->SetPointId(0, cellId);     // first point
    line->SetPointId(1, cellId + 1); // second point
    mesh->SetCell(cellId, line);     // insert the cell
  }

  std::cout << "Points = " << mesh->GetNumberOfPoints() << std::endl;
  std::cout << "Cells  = " << mesh->GetNumberOfCells() << std::endl << std::endl;

  // assign data to cells
  for (unsigned int cellId = 0; cellId < numberOfCells; cellId++)
  {
    mesh->SetCellData(cellId, static_cast<PixelType>(cellId * cellId));
  }

  // retrieve data from cells
  for (unsigned int cellId = 0; cellId < numberOfCells; ++cellId)
  {
    PixelType value = static_cast<PixelType>(0.0);
    mesh->GetCellData(cellId, &value);
    std::cout << "Cell " << cellId << " = " << value << std::endl;
  }

  // access via an iterator
  using CellDataIterator = MeshType::CellDataContainer::ConstIterator;
  CellDataIterator cellDataIterator = mesh->GetCellData()->Begin();
  CellDataIterator end = mesh->GetCellData()->End();

  while (cellDataIterator != end)
  {
    const PixelType cellValue = cellDataIterator.Value();
    (void)cellValue; // Avoid unused variable warning for this example code
    // std::cout << cellValue << std::endl; //same values as before
    ++cellDataIterator;
  }

  return EXIT_SUCCESS;
}
