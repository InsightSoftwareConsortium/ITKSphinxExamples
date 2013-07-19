cmake_minimum_required( VERSION 2.8 )

project( ObserveAnEvent )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ObserveAnEvent Code.cxx )
target_link_libraries( ObserveAnEvent ${ITK_LIBRARIES} )

install( TARGETS ObserveAnEvent
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/ObserveAnEvent
  COMPONENT Code
)

enable_testing()
add_test( NAME ObserveAnEventTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ObserveAnEvent )
