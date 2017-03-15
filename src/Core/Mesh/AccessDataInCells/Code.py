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
# CellTraits = itk.itkCellTraitsInfo._2FFULLULLULLPF2MCULLPF2
# CellType = itk.CellInterface[PixelType, CellTraits]()
# LineType = itk.LineCell()


mesh = MeshType.New()

point = PointType()

number_of_points = 10
for point_id in range(number_of_points):
    point[0] = float(point_id)
    point[1] = np.log(float(point_id) + np.finfo(float).eps)
    mesh.SetPoint(point_id, point)

number_of_cells = number_of_points - 1
# for cell_id in range(number_of_cells):
#
# CellType::CellAutoPointer line;
# const unsigned int numberOfCells = numberOfPoints-1;
# for(unsigned int cellId=0; cellId<numberOfCells; cellId++)
#   {
#   line.TakeOwnership(  new LineType  );
#   line->SetPointId( 0, cellId   ); // first point
#   line->SetPointId( 1, cellId+1 ); // second point
#   mesh->SetCell( cellId, line );   // insert the cell
#   }
#
# std::cout << "Points = " << mesh->GetNumberOfPoints() << std::endl;
# std::cout << "Cells  = " << mesh->GetNumberOfCells()  << std::endl << std::endl;
#
# # assign data to cells
# for(unsigned int cellId=0; cellId<numberOfCells; cellId++)
#   {
#   mesh->SetCellData( cellId, static_cast<PixelType>( cellId * cellId ) );
#   }
#
# # retrieve data from cells
# for(unsigned int cellId=0; cellId<numberOfCells; ++cellId)
#   {
#   PixelType value = static_cast<PixelType>(0.0);
#   mesh->GetCellData( cellId, &value );
#   std::cout << "Cell " << cellId << " = " << value << std::endl;
#   }
