cmake_minimum_required(VERSION 3.10.2)

project( CutMesh )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CutMesh Code.cxx )
target_link_libraries( CutMesh ${ITK_LIBRARIES} )

install( TARGETS CutMesh
  DESTINATION bin/ITKSphinxExamples/Core/QuadEdgeMesh
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/QuadEdgeMesh/CutMesh
  COMPONENT Code
  )

enable_testing()
add_test( NAME CutMeshTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CutMesh
    ${CMAKE_CURRENT_BINARY_DIR}/genusZeroSurface01.vtk
    CutMeshTestOutput.vtk
)
