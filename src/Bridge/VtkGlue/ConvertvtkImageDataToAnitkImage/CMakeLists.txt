cmake_minimum_required(VERSION 2.8.9)

project(ConvertvtkImageDataToAnitkImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# Since we use vtkImageMagnitude
find_package(VTK REQUIRED COMPONENTS vtkImagingMath)
include(${VTK_USE_FILE})


add_executable(ConvertvtkImageDataToAnitkImage Code.cxx)
target_link_libraries(ConvertvtkImageDataToAnitkImage
  ${ITK_LIBRARIES}
  ${VTK_LIBRARIES}
  )

install(TARGETS ConvertvtkImageDataToAnitkImage
  DESTINATION bin/ITKExamples/Bridge/VtkGlue
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Bridge/VtkGlue/ConvertvtkImageDataToAnitkImage/
  COMPONENT Code
  )


enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png)

add_test(NAME ConvertvtkImageDataToAnitkImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertvtkImageDataToAnitkImage
    ${input_image}
  )
