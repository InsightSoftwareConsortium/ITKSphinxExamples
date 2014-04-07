cmake_minimum_required( VERSION 2.8.5 )

project( ImageRegionIntersection )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ImageRegionIntersection Code.cxx )
target_link_libraries( ImageRegionIntersection ${ITK_LIBRARIES} )

install( TARGETS ImageRegionIntersection
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/ImageRegionIntersection
  COMPONENT Code
)

enable_testing()
add_test( NAME ImageRegionIntersectionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImageRegionIntersection )
