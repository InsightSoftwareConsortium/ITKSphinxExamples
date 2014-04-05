project( ConceptCheckingIsSameDimension )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ConceptCheckingIsSameDimension Code.cxx )
target_link_libraries( ConceptCheckingIsSameDimension ${ITK_LIBRARIES} )

install( TARGETS ConceptCheckingIsSameDimension
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/ConceptCheckingIsSameDimension
  COMPONENT Code
  )

enable_testing()
add_test( NAME ConceptCheckingIsSameDimensionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConceptCheckingIsSameDimension )
