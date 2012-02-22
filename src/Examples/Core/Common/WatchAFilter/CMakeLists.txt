cmake_minimum_required( VERSION 2.8 )

project( WatchAFilter )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( WatchAFilter WatchAFilter.cxx )
target_link_libraries( WatchAFilter ${ITK_LIBRARIES} )

install( TARGETS WatchAFilter
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES WatchAFilter.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/WatchAFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME WatchAFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WatchAFilter )
