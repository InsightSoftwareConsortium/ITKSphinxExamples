#!/usr/bin/env python

# ==========================================================================
#
#   Copyright Insight Software Consortium
#
#   Licensed under the Apache License, Version 2.0 (the "License")
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
# ==========================================================================*/

import sys
import itk
import numpy as np

Dimension = 2
PixelType = itk.F  # float or double

MeshType = itk.Mesh[PixelType, Dimension]
PointType = itk.Point[itk.D, Dimension]

mesh = MeshType.New()

number_of_points = 10
for point_id in range(number_of_points):
    point = [float(point_id), np.log(float(point_id) + np.finfo(float).eps)]
    mesh.SetPoint(point_id, point)

number_of_cells = number_of_points - 1

# All cells are of type LINE so creating numpy of shape [number_of_cells x 2]
cells_array = np.zeros([number_of_cells, 2], dtype=np.uint64)

for cell_id in range(number_of_cells):
    cells_array[cell_id][0] = cell_id
    cells_array[cell_id][1] = cell_id + 1

cells_vector = itk.vector_container_from_array(cells_array.flatten())

# When all cells are same use the second arguement to pass the cell type
mesh.SetCellsArray(cells_vector, itk.CommonEnums.CellGeometry_LINE_CELL)

print("Points = ", mesh.GetNumberOfPoints())
print("Cells = ", mesh.GetNumberOfCells())

# Assign data to cells

# This can also be done by setting large array in one function call
# which would be more efficient than the following approach
for cell_id in range(number_of_cells):
    mesh.SetCellData(cell_id, cell_id * cell_id)


# Retrieve data from cells
cell_data = mesh.GetCellData()

# Obtain numpy array from the vector_container
cell_data_np = itk.array_from_vector_container(cell_data)

for cell_id in range(number_of_cells):
    # Demonstrating two ways of getting the element
    # First using GetElement and second using the numpy array
    if cell_id % 2 == 0:
        print("Cell ", cell_id, " = ", cell_data.GetElement(cell_id))
    else:
        temp = cell_data_np[cell_id]
        print("Cell ", cell_id, " = ", cell_data_np[cell_id])
