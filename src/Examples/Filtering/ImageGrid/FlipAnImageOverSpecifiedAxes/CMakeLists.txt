cmake_minimum_required( VERSION 2.8 )

project( FlipAnImageOverSpecifiedAxes )

find_package( ITK REQUIRED )

if( ${ITK_FOUND} )
  include( ${ITK_USE_FILE} )
endif()

add_executable( FlipAnImageOverSpecifiedAxes FlipAnImageOverSpecifiedAxes.cxx )
target_link_libraries( FlipAnImageOverSpecifiedAxes ${ITK_LIBRARIES} )

enable_testing()
add_test( FlipAnImageOverSpecifiedAxesTest FlipAnImageOverSpecifiedAxes )
