cmake_minimum_required( VERSION 2.8.6 )

project( PrintVertexNeighbors )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( PrintVertexNeighbors Code.cxx )
target_link_libraries( PrintVertexNeighbors ${ITK_LIBRARIES} )

install( TARGETS PrintVertexNeighbors
  DESTINATION bin/ITKExamples/Core/QuadEdgeMesh
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/QuadEdgeMesh/PrintVertexNeighbors
  COMPONENT Code
  )

enable_testing()
add_test( NAME PrintVertexNeighborsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PrintVertexNeighbors ${CMAKE_CURRENT_BINARY_DIR}/wave.vtk 50 )
