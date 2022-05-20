cmake_minimum_required(VERSION 3.16.3)

project(DelaunayConformEdgeFlipping)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(DelaunayConformEdgeFlipping Code.cxx)
target_link_libraries(DelaunayConformEdgeFlipping ${ITK_LIBRARIES})

install(TARGETS DelaunayConformEdgeFlipping
  DESTINATION bin/ITKSphinxExamples/Filtering/QuadEdgeMeshFiltering
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/QuadEdgeMeshFiltering/DelaunayConformEdgeFlipping
  COMPONENT Code
)

enable_testing()
add_test(NAME DelaunayConformEdgeFlippingTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DelaunayConformEdgeFlipping
  mushroom.vtk
  Output.vtk
)
