cmake_minimum_required(VERSION 3.22.1)

project(ComputeNormalsOfAMesh)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKMeshIO
    ITK::ITKCommonModule
    ITK::ITKQuadEdgeMeshModule
    ITK::ITKQuadEdgeMeshFilteringModule
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/QuadEdgeMeshFiltering
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Filtering/QuadEdgeMeshFiltering/ComputeNormalsOfAMesh
  COMPONENT Code
)

enable_testing()
add_test(
  NAME ComputeNormalsOfAMeshTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/genusZeroSurface01.vtk 0
)
