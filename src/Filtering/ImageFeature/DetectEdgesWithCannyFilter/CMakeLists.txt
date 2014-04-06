cmake_minimum_required( VERSION 2.8.5 )

project( DetectEdgesWithCannyFilter )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( DetectEdgesWithCannyFilter Code.cxx )
target_link_libraries( DetectEdgesWithCannyFilter ${ITK_LIBRARIES} )

install( TARGETS DetectEdgesWithCannyFilter
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/DetectEdgesWithCannyFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME DetectEdgesWithCannyFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DetectEdgesWithCannyFilter
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    Output.png
    1
    30
    15
)
