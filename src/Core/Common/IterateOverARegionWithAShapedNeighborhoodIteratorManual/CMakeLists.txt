cmake_minimum_required(VERSION 3.10.2)

project( IterateOverARegionWithAShapedNeighborhoodIteratorManual )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( IterateOverARegionWithAShapedNeighborhoodIteratorManual Code.cxx )
target_link_libraries( IterateOverARegionWithAShapedNeighborhoodIteratorManual ${ITK_LIBRARIES} )

install( TARGETS IterateOverARegionWithAShapedNeighborhoodIteratorManual
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateOverARegionWithAShapedNeighborhoodIteratorManual
  COMPONENT Code
)

enable_testing()
add_test( NAME IterateOverARegionWithAShapedNeighborhoodIteratorManualTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateOverARegionWithAShapedNeighborhoodIteratorManual )
