cmake_minimum_required( VERSION 2.8 )

project( FlipAnImageOverSpecifiedAxes )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( FlipAnImageOverSpecifiedAxes FlipAnImageOverSpecifiedAxes.cxx )
target_link_libraries( FlipAnImageOverSpecifiedAxes ${ITK_LIBRARIES} )

install( TARGETS FlipAnImageOverSpecifiedAxes
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
)

enable_testing()
add_test( FlipAnImageOverSpecifiedAxesTest FlipAnImageOverSpecifiedAxes
  ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png FlipAnImageOverSpecifiedAxesOutput.png 0
  )
