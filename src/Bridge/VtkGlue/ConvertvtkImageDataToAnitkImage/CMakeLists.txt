cmake_minimum_required(VERSION 3.22.1)

project(ConvertvtkImageDataToAnitkImage)

find_package(ITK REQUIRED)

# Since we use vtkImageMagnitude
find_package(VTK REQUIRED COMPONENTS ImagingMath)

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKVtkGlueModule
    ${VTK_LIBRARIES}
)

vtk_module_autoinit(
  TARGETS ConvertvtkImageDataToAnitkImage
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
    Code.py
  DESTINATION
    share/ITKSphinxExamples/Code/Bridge/VtkGlue/ConvertvtkImageDataToAnitkImage/
  COMPONENT Code
)

enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png)

add_test(
  NAME ConvertvtkImageDataToAnitkImageTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${input_image}
)
