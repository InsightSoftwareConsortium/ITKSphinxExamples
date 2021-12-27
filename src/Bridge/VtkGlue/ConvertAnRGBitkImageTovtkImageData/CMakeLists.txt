cmake_minimum_required(VERSION 3.16.3)

project(ConvertAnRGBitkImageTovtkImageData)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ConvertAnRGBitkImageTovtkImageData Code.cxx)
target_link_libraries(ConvertAnRGBitkImageTovtkImageData ${ITK_LIBRARIES})

install(TARGETS ConvertAnRGBitkImageTovtkImageData
  DESTINATION bin/ITKSphinxExamples/Bridge/VtkGlue
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Bridge/VtkGlue/ConvertAnRGBitkImageTovtkImageData/
  COMPONENT Code
  )


enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/VisibleWomanEyeSlice.png)

add_test(NAME ConvertAnRGBitkImageTovtkImageDataTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertAnRGBitkImageTovtkImageData
  ${input_image}
  )
