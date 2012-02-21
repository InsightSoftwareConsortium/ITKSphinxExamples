cmake_minimum_required( VERSION 2.8 )

project( DistanceBetweenPoints )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( DistanceBetweenPoints DistanceBetweenPoints.cxx )
target_link_libraries( DistanceBetweenPoints ${ITK_LIBRARIES} )

install( TARGETS DistanceBetweenPoints
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES DistanceBetweenPoints.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/DistanceBetweenPoints
  COMPONENT Code
)

enable_testing()
add_test( NAME DistanceBetweenPointsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DistanceBetweenPoints )
