cmake_minimum_required( VERSION 2.8 )

project( GetTypeBasicInformation )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( GetTypeBasicInformation GetTypeBasicInformation.cxx )
target_link_libraries( GetTypeBasicInformation ${ITK_LIBRARIES} )

install( TARGETS GetTypeBasicInformation
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES GetTypeBasicInformation.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/GetTypeBasicInformation
  COMPONENT Code
)

enable_testing()
add_test( NAME GetTypeBasicInformationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GetTypeBasicInformation )
