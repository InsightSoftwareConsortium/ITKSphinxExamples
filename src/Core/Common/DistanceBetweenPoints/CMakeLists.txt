cmake_minimum_required( VERSION 2.8.5 )

project( DistanceBetweenPoints )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( DistanceBetweenPoints Code.cxx )
target_link_libraries( DistanceBetweenPoints ${ITK_LIBRARIES} )

install( TARGETS DistanceBetweenPoints
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/DistanceBetweenPoints
  COMPONENT Code
)

enable_testing()
add_test( NAME DistanceBetweenPointsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DistanceBetweenPoints )
