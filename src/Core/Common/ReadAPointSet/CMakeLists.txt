cmake_minimum_required(VERSION 3.16.3)

project( ReadAPointSet )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ReadAPointSet Code.cxx )
target_link_libraries( ReadAPointSet ${ITK_LIBRARIES} )

install( TARGETS ReadAPointSet
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/ReadAPointSet
  COMPONENT Code
)

enable_testing()
add_test( NAME ReadAPointSetTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ReadAPointSet
)
