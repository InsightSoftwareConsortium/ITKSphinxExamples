cmake_minimum_required(VERSION 3.10.2)

project( TraceMemoryBetweenPoints )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( TraceMemoryBetweenPoints Code.cxx )
target_link_libraries( TraceMemoryBetweenPoints ${ITK_LIBRARIES} )

install( TARGETS TraceMemoryBetweenPoints
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/TraceMemoryBetweenPoints
  COMPONENT Code
  )

enable_testing()
add_test( NAME TraceMemoryBetweenPointsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TraceMemoryBetweenPoints 2048000 )
