cmake_minimum_required( VERSION 2.8.6 )

project( SegmentBloodVessels )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( SegmentBloodVessels Code.cxx )
target_link_libraries( SegmentBloodVessels ${ITK_LIBRARIES} )

install( TARGETS SegmentBloodVessels
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/SegmentBloodVessels
  COMPONENT Code
  )

enable_testing()
add_test( NAME SegmentBloodVesselsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SegmentBloodVessels
    ${CMAKE_CURRENT_BINARY_DIR}/HeadMRA.mha
    Output.mha
    2.0
  )
set_tests_properties( SegmentBloodVesselsTest PROPERTIES
  LABELS RUNS_LONG )
