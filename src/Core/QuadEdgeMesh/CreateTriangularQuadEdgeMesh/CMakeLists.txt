cmake_minimum_required(VERSION 3.16.3)

project(CreateTriangularQuadEdgeMesh)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(CreateTriangularQuadEdgeMesh Code.cxx)
target_link_libraries(CreateTriangularQuadEdgeMesh ${ITK_LIBRARIES})

install(TARGETS CreateTriangularQuadEdgeMesh
  DESTINATION bin/ITKSphinxExamples/Core/QuadEdgeMesh
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/QuadEdgeMesh/CreateTriangularQuadEdgeMesh
  COMPONENT Code
  )

enable_testing()
add_test(NAME CreateTriangularQuadEdgeMeshTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateTriangularQuadEdgeMesh
    Output.vtk
  )
