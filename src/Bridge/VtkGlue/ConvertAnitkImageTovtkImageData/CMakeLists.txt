cmake_minimum_required(VERSION 3.8.2)

project(ConvertAnitkImageTovtkImageData)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ConvertAnitkImageTovtkImageData Code.cxx)
target_link_libraries(ConvertAnitkImageTovtkImageData ${ITK_LIBRARIES})

install(TARGETS ConvertAnitkImageTovtkImageData
  DESTINATION bin/ITKExamples/Bridge/VtkGlue
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKExamples/Code/Bridge/VtkGlue/ConvertAnitkImageTovtkImageData/
  COMPONENT Code
  )


enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png)

add_test(NAME ConvertAnitkImageTovtkImageDataTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertAnitkImageTovtkImageData
    ${input_image}
  )
