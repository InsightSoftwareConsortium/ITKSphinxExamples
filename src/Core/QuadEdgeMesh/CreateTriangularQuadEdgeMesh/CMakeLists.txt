cmake_minimum_required( VERSION 2.8.6 )

project( CreateTriangularQuadEdgeMesh )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateTriangularQuadEdgeMesh Code.cxx )
target_link_libraries( CreateTriangularQuadEdgeMesh ${ITK_LIBRARIES} )

install( TARGETS CreateTriangularQuadEdgeMesh
  DESTINATION bin/ITKExamples/Core/QuadEdgeMesh
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/QuadEdgeMesh/CreateTriangularQuadEdgeMesh
  COMPONENT Code
  )

enable_testing()
add_test( NAME CreateTriangularQuadEdgeMeshTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateTriangularQuadEdgeMesh
    Output.vtk
  )
