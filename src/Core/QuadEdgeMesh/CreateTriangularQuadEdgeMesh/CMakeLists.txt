cmake_minimum_required(VERSION 3.22.1)

project(CreateTriangularQuadEdgeMesh)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKMeshIO
    ITK::ITKQuadEdgeMeshModule
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/QuadEdgeMesh
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Core/QuadEdgeMesh/CreateTriangularQuadEdgeMesh
  COMPONENT Code
)

enable_testing()
add_test(
  NAME CreateTriangularQuadEdgeMeshTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} Output.vtk
)
