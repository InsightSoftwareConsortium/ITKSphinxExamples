cmake_minimum_required(VERSION 3.22.1)

project(MakeOutOfBoundsPixelsReturnConstValue)

find_package(ITK REQUIRED)

find_package(VTK REQUIRED)
find_package(
  VTK
  REQUIRED
  COMPONENTS
    InteractionImage
    InteractionStyle
    RenderingCore
    RenderingGL2PSOpenGL2
)

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKCommonModule
    ITK::ITKVtkGlueModule
    ${VTK_LIBRARIES}
)

vtk_module_autoinit(
  TARGETS MakeOutOfBoundsPixelsReturnConstValue
  MODULES ${VTK_LIBRARIES}
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Core/Common/MakeOutOfBoundsPixelsReturnConstValue/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME MakeOutOfBoundsPixelsReturnConstValueTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)
