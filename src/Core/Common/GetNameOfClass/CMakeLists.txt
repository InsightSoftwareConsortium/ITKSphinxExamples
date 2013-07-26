cmake_minimum_required( VERSION 2.8 )

project( GetNameOfClass )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( GetNameOfClass Code.cxx )
target_link_libraries( GetNameOfClass ${ITK_LIBRARIES} )

install( TARGETS GetNameOfClass
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/GetNameOfClass
  COMPONENT Code
)

enable_testing()
add_test( NAME GetNameOfClassTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GetNameOfClass )
