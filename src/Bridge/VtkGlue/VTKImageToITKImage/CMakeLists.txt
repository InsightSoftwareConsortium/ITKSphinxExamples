cmake_minimum_required(VERSION 3.22.1)

project(VTKImageToITKImage)

find_package(ITK REQUIRED)

find_package(VTK REQUIRED)
find_package(
  VTK
  REQUIRED
  COMPONENTS
    ImagingColor
    IOImage
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
  TARGETS VTKImageToITKImage
  MODULES ${VTK_LIBRARIES}
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Bridge/VtkGlue
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Bridge/VtkGlue/VTKImageToITKImage/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME VTKImageToITKImageTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} Gourds.png
)
