cmake_minimum_required(VERSION 3.22.1)

project(CalculateAreaAndVolumeOfSimplexMesh)

find_package(ITK REQUIRED)

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} PRIVATE ITK::ITKMeshModule)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Mesh
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Core/Mesh/CalculateAreaAndVolumeOfSimplexMesh/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME CalculateAreaAndVolumeOfSimplexMeshTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)
