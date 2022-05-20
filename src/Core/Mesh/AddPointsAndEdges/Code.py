#!/usr/bin/env python

# Copyright NumFOCUS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


import itk
import numpy as np

Dimension = 3
MeshType = itk.Mesh[itk.F, Dimension]


def CreatePointOnlyMesh():
    mesh = MeshType.New()

    # Create points
    p0 = [-1.0, -1.0, 0.0]  # first  point ( -1, -1, 0 )
    p1 = [1.0, -1.0, 0.0]  # second point (  1, -1, 0 )
    p2 = [1.0, 1.0, 0.0]  # third  point (  1,  1, 0 )
    p3 = [1.0, 1.0, 1.0]  # fourth  point (  1,  1, 1 )

    mesh.SetPoint(0, p0)
    mesh.SetPoint(1, p1)
    mesh.SetPoint(2, p2)
    mesh.SetPoint(3, p3)

    print("Points = ", mesh.GetNumberOfPoints())

    # Access points
    points = mesh.GetPoints()
    for i in range(points.Size()):
        p = mesh.GetPoint(i)
        print(p)

    return mesh


def CreateMeshWithEdges():
    mesh = CreatePointOnlyMesh()

    # Point Ids for the two cells
    pointId0 = 0
    pointId1 = 1

    pointId2 = 1
    pointId3 = 2

    # Create cells array and insert points in them
    # Each cell is of line type here
    cells_array = np.zeros(4, dtype=np.uint64)
    cells_array[0] = pointId0
    cells_array[1] = pointId1

    cells_array[2] = pointId2
    cells_array[3] = pointId3

    cells_vector = itk.vector_container_from_array(cells_array.flatten())

    # When all cells are same use the second arguement to pass the cell type
    mesh.SetCellsArray(cells_vector, itk.CommonEnums.CellGeometry_LINE_CELL)

    number_of_cells = mesh.GetNumberOfCells()
    all_cells = mesh.GetCells()

    # Iterate over the cells and print the points present in them
    for i in range(number_of_cells):
        current_cell = all_cells.GetElement(i)
        point_ids = current_cell.GetPointIdsContainer()
        print(point_ids)


CreateMeshWithEdges()
