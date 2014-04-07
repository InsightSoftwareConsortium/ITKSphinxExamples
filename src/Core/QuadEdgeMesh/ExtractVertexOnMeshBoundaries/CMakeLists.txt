cmake_minimum_required( VERSION 2.8.5 )

project( ExtractVertexOnMeshBoundaries )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ExtractVertexOnMeshBoundaries
  Code.cxx )
target_link_libraries( ExtractVertexOnMeshBoundaries ${ITK_LIBRARIES} )

install( TARGETS ExtractVertexOnMeshBoundaries
  DESTINATION bin/ITKExamples/Core/QuadEdgeMesh
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/QuadEdgeMesh/ExtractVertexOnMeshBoundaries
  COMPONENT Code
  )

enable_testing()
add_test( NAME ExtractVertexOnMeshBoundariesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExtractVertexOnMeshBoundaries
    ${CMAKE_CURRENT_BINARY_DIR}/wave.vtk
)
