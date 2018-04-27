cmake_minimum_required(VERSION 3.10.2)

project( ComputeNormalsOfAMesh )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ComputeNormalsOfAMesh Code.cxx )
target_link_libraries( ComputeNormalsOfAMesh ${ITK_LIBRARIES} )

install( TARGETS ComputeNormalsOfAMesh
  DESTINATION bin/ITKExamples/Filtering/QuadEdgeMeshFiltering
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/QuadEdgeMeshFiltering/ComputeNormalsOfAMesh
  COMPONENT Code
)

enable_testing()
add_test( NAME ComputeNormalsOfAMeshTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeNormalsOfAMesh
    ${CMAKE_CURRENT_BINARY_DIR}/genusZeroSurface01.vtk
    0
)
