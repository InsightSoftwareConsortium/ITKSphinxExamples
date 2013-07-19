cmake_minimum_required( VERSION 2.8 )

project( IterateOverARegionWithAShapedNeighborhoodIterator )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( IterateOverARegionWithAShapedNeighborhoodIterator Code.cxx )
target_link_libraries( IterateOverARegionWithAShapedNeighborhoodIterator ${ITK_LIBRARIES} )

install( TARGETS IterateOverARegionWithAShapedNeighborhoodIterator
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/IterateOverARegionWithAShapedNeighborhoodIterator
  COMPONENT Code
)

enable_testing()
add_test( NAME IterateOverARegionWithAShapedNeighborhoodIteratorTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/IterateOverARegionWithAShapedNeighborhoodIterator )
