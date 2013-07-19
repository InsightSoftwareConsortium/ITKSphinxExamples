cmake_minimum_required( VERSION 2.8 )

project( FlipAnImageOverSpecifiedAxes )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( FlipAnImageOverSpecifiedAxes Code.cxx )
target_link_libraries( FlipAnImageOverSpecifiedAxes ${ITK_LIBRARIES} )

install( TARGETS FlipAnImageOverSpecifiedAxes
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/FlipAnImageOverSpecifiedAxes
  COMPONENT Code
)

enable_testing()
add_test( NAME FlipAnImageOverSpecifiedAxesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FlipAnImageOverSpecifiedAxes ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png Output.png 0
)
