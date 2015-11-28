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

#include "itkVTKPolyDataReader.h"

#include "itkImage.h"
#include "itkPointSet.h"

#include <string>
#include <iostream>

int main( int argc, char *argv[] )
{
  if (argc < 2)
    {
    std::cout << "Usage: " << argv[0]
              << " Input(.vtk)" << std::endl;
    return EXIT_FAILURE;
    }

  std::string InputFilename = argv[1];
  std::cout << "Input file: " << InputFilename << std::endl;

  //typedef itk::PointSet<double, 3 > PointSetType;
  //PointSetType::Pointer pointsSet = PointSetType::New();
  //typedef PointSetType::PointType PointType;

  const unsigned int Dimension = 3;

  typedef float                               CoordType;
  typedef itk::Mesh< CoordType, Dimension >   MeshType;

  typedef itk::VTKPolyDataReader< MeshType >  ReaderType;
  ReaderType::Pointer  polyDataReader = ReaderType::New();

  typedef ReaderType::PointType   PointType;
  typedef ReaderType::VectorType  VectorType;

  polyDataReader->SetFileName( InputFilename.c_str() );

  try
    {
    polyDataReader->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }

  std::cout << "polyDataReader:" << std::endl;
  std::cout << polyDataReader << std::endl;

  MeshType::Pointer mesh = polyDataReader->GetOutput();

  PointType  point;

  std::cout << "Testing itk::VTKPolyDataReader" << std::endl;

  unsigned int numberOfPoints = mesh->GetNumberOfPoints();
  unsigned int numberOfCells  = mesh->GetNumberOfCells();

  std::cout << "numberOfPoints= " << numberOfPoints << std::endl;
  std::cout << "numberOfCells= " << numberOfCells << std::endl;

  if( !numberOfPoints )
    {
    std::cerr << "ERROR: numberOfPoints= " << numberOfPoints << std::endl;
    return EXIT_FAILURE;
    }

  if( !numberOfCells )
    {
    std::cerr << "ERROR: numberOfCells= " << numberOfCells << std::endl;
    return EXIT_FAILURE;
    }

  // Retrieve points
  for( unsigned int i = 0; i < numberOfPoints; i++ )
    {
    PointType pp;
    bool pointExists = mesh->GetPoint( i, &pp );

    if( pointExists )
      {
      std::cout << "Point is = " << pp << std::endl;
      }
    }
  return EXIT_SUCCESS;
}
