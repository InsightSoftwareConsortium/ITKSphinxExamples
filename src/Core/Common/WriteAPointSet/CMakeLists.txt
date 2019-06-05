cmake_minimum_required(VERSION 3.10.2)

project( WriteAPointSet )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( WriteAPointSet Code.cxx )
target_link_libraries( WriteAPointSet ${ITK_LIBRARIES} )

install( TARGETS WriteAPointSet
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/WriteAPointSet
  COMPONENT Code
)

enable_testing()
add_test( NAME WriteAPointSetTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ReadAPointSet
)
