cmake_minimum_required( VERSION 2.8.6 )

project( ConceptCheckingIsSameType )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ConceptCheckingIsSameType Code.cxx )
target_link_libraries( ConceptCheckingIsSameType ${ITK_LIBRARIES} )

install( TARGETS ConceptCheckingIsSameType
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/ConceptCheckingIsSameType
  COMPONENT Code
  )

enable_testing()
add_test( NAME ConceptCheckingIsSameTypeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConceptCheckingIsSameType )
