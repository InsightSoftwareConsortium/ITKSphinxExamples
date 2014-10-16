cmake_minimum_required( VERSION 2.8.6 )

project( GetTypeBasicInformation )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( GetTypeBasicInformation Code.cxx )
target_link_libraries( GetTypeBasicInformation ${ITK_LIBRARIES} )

install( TARGETS GetTypeBasicInformation
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/GetTypeBasicInformation
  COMPONENT Code
)

enable_testing()
add_test( NAME GetTypeBasicInformationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GetTypeBasicInformation )
