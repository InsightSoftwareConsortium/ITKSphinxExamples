cmake_minimum_required(VERSION 3.16.3)

project(CalculateAreaAndVolumeOfSimplexMesh)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CalculateAreaAndVolumeOfSimplexMesh Code.cxx)
target_link_libraries(CalculateAreaAndVolumeOfSimplexMesh ${ITK_LIBRARIES})

install(TARGETS CalculateAreaAndVolumeOfSimplexMesh
  DESTINATION bin/ITKSphinxExamples/Core/Mesh
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Mesh/CalculateAreaAndVolumeOfSimplexMesh/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CalculateAreaAndVolumeOfSimplexMeshTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CalculateAreaAndVolumeOfSimplexMesh)

