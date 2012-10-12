cmake_minimum_required( VERSION 2.8 )

project( DelaunayConformEdgeFlipping )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( DelaunayConformEdgeFlipping DelaunayConformEdgeFlipping.cxx )
target_link_libraries( DelaunayConformEdgeFlipping ${ITK_LIBRARIES} )

install( TARGETS DelaunayConformEdgeFlipping
  DESTINATION bin/ITKExamples/Filtering/QuadEdgeMeshFiltering
  COMPONENT Runtime
)

install( FILES DelaunayConformEdgeFlipping.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/QuadEdgeMeshFiltering/DelaunayConformEdgeFlipping
  COMPONENT Code
)

enable_testing()
add_test( NAME DelaunayConformEdgeFlippingTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DelaunayConformEdgeFlipping
  wave.vtk
  DelaunayConformEdgeFlippingOutput.vtk
)
