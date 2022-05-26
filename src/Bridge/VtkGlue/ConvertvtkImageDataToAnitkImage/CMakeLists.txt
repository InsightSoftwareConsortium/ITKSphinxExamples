cmake_minimum_required(VERSION 3.16.3)

project(ConvertvtkImageDataToAnitkImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# Since we use vtkImageMagnitude
find_package(VTK REQUIRED
  COMPONENTS
    ImagingMath
  )
if(VTK_VERSION VERSION_LESS "8.90.0")
  include(${VTK_USE_FILE})
endif()

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME}
  ${ITK_LIBRARIES}
  ${VTK_LIBRARIES}
  )

if(NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS ConvertvtkImageDataToAnitkImage
    MODULES ${VTK_LIBRARIES}
    )
endif()

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Bridge/VtkGlue
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Bridge/VtkGlue/ConvertvtkImageDataToAnitkImage/
  COMPONENT Code
  )


enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png)

add_test(NAME ConvertvtkImageDataToAnitkImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
  )
