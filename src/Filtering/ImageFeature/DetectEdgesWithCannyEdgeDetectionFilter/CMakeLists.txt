cmake_minimum_required(VERSION 3.10.2)

project( DetectEdgesWithCannyEdgeDetectionFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( DetectEdgesWithCannyEdgeDetectionFilter Code.cxx )
target_link_libraries( DetectEdgesWithCannyEdgeDetectionFilter ${ITK_LIBRARIES} )

install( TARGETS DetectEdgesWithCannyEdgeDetectionFilter
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/DetectEdgesWithCannyEdgeDetectionFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME DetectEdgesWithCannyEdgeDetectionFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DetectEdgesWithCannyEdgeDetectionFilter
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    Output.png
    1
    15
    30
  )

if( ITK_WRAP_PYTHON )
  add_test( NAME DetectEdgesWithCannyEdgeDetectionFilterTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
      OutputPython.png
      1
      15
      30
    )
endif()
