cmake_minimum_required(VERSION 3.10.2)

project( IterateOnAVectorContainer )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( IterateOnAVectorContainer Code.cxx )
target_link_libraries( IterateOnAVectorContainer ${ITK_LIBRARIES} )

install( TARGETS IterateOnAVectorContainer
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateOnAVectorContainer
  COMPONENT Code
)

enable_testing()
add_test( NAME IterateOnAVectorContainerTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateOnAVectorContainer )
