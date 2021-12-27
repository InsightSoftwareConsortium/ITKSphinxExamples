cmake_minimum_required(VERSION 3.16.3)

project(ConvertRGBvtkImageDataToAnitkImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ConvertRGBvtkImageDataToAnitkImage Code.cxx)
target_link_libraries(ConvertRGBvtkImageDataToAnitkImage ${ITK_LIBRARIES})

install(TARGETS ConvertRGBvtkImageDataToAnitkImage
  DESTINATION bin/ITKSphinxExamples/Bridge/VtkGlue
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Bridge/VtkGlue/ConvertRGBvtkImageDataToAnitkImage/
  COMPONENT Code
  )


enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/VisibleWomanEyeSlice.png)

add_test(NAME ConvertRGBvtkImageDataToAnitkImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertRGBvtkImageDataToAnitkImage
    ${input_image}
  )
