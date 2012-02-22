cmake_minimum_required( VERSION 2.8 )

project( IterateOnAVectorContainer )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( IterateOnAVectorContainer IterateOnAVectorContainer.cxx )
target_link_libraries( IterateOnAVectorContainer ${ITK_LIBRARIES} )

install( TARGETS IterateOnAVectorContainer
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES IterateOnAVectorContainer.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateOnAVectorContainer
  COMPONENT Code
)

enable_testing()
add_test( NAME IterateOnAVectorContainerTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateOnAVectorContainer )
