cmake_minimum_required(VERSION 3.16.3)

project(ReadMesh)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(ReadMesh Code.cxx)
target_link_libraries(ReadMesh ${ITK_LIBRARIES})

install(TARGETS ReadMesh
  DESTINATION bin/ITKSphinxExamples/IO/Mesh
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/IO/Mesh/ReadMesh
  COMPONENT Code
  )

enable_testing()

add_test(NAME ReadMeshTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ReadMesh
    ${CMAKE_CURRENT_BINARY_DIR}/genusZeroSurface01.vtk 0 25
)
