cmake_minimum_required(VERSION 3.22.1)

project(DetectEdgesWithCannyEdgeDetectionFilter)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFeature/DetectEdgesWithCannyEdgeDetectionFilter
  COMPONENT Code
)

enable_testing()
add_test(NAME DetectEdgesWithCannyEdgeDetectionFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    Output.png
    1
    15
    30
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME DetectEdgesWithCannyEdgeDetectionFilterTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
      OutputPython.png
      1
      15
      30
    )
endif()
