cmake_minimum_required(VERSION 3.16.3)

project(ConvertRGBImageToGrayscaleImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/ConvertRGBImageToGrayscaleImage
  COMPONENT Code
)

enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/itk_eg_logo.png)
set(output_image Output.png)

add_test(NAME ConvertRGBImageToGrayscaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    ${output_image}
)

if(ITK_WRAP_PYTHON)
  find_package(Python3 COMPONENTS Interpreter REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME ConvertRGBImageToGrayscaleImageTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
    )
endif()
