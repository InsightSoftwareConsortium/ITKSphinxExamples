cmake_minimum_required(VERSION 3.16.3)

project(AdditiveGaussianNoiseImageFilter)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFeature/AdditiveGaussianNoiseImageFilter
  COMPONENT Code
)

enable_testing()
add_test(NAME AdditiveGaussianNoiseImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
  ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
  Output.png
  20
  1
  )

if(ITK_WRAP_PYTHON)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
    add_test(NAME AdditiveGaussianNoiseImageFilterTestPython
      COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
      OutputPython.png
      20
      1
      )
endif()