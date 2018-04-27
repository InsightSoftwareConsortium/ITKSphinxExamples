cmake_minimum_required(VERSION 3.10.2)

project( ConceptCheckingIsFloatingPoint )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ConceptCheckingIsFloatingPoint Code.cxx )
target_link_libraries( ConceptCheckingIsFloatingPoint ${ITK_LIBRARIES} )

install( TARGETS ConceptCheckingIsFloatingPoint
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/ConceptCheckingIsFloatingPoint
  COMPONENT Code
  )

enable_testing()
add_test( NAME ConceptCheckingIsFloatingPointTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConceptCheckingIsFloatingPoint )
