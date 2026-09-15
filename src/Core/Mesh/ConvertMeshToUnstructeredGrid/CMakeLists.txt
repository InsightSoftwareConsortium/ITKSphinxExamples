cmake_minimum_required(VERSION 3.22.1)

project(ConvertMeshToUnstructeredGrid)

find_package(ITK REQUIRED)

find_package(VTK REQUIRED)
find_package(
  VTK
  REQUIRED
  COMPONENTS
    IOXML
    CommonDataModel
    InteractionImage
)

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKCommonModule
    ITK::ITKMeshModule
    ${VTK_LIBRARIES}
)

vtk_module_autoinit(
  TARGETS WatchRegistration
  MODULES ${VTK_LIBRARIES}
)

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
    share/ITKSphinxExamples/Code/Core/Mesh/ConvertMeshToUnstructeredGrid/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME ConvertMeshToUnstructeredGridTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)
