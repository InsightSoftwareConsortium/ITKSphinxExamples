cmake_minimum_required(VERSION 3.16.3)

project(CleanQuadEdgeMesh)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(CleanQuadEdgeMesh Code.cxx)
target_link_libraries(CleanQuadEdgeMesh ${ITK_LIBRARIES})

install(TARGETS CleanQuadEdgeMesh
  DESTINATION bin/ITKSphinxExamples/Filtering/QuadEdgeMeshFiltering
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/QuadEdgeMeshFiltering/CleanQuadEdgeMesh
  COMPONENT Code
)

enable_testing()
add_test(NAME CleanQuadEdgeMeshTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CleanQuadEdgeMesh)
