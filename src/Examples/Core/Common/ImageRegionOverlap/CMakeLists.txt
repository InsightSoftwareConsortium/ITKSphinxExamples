cmake_minimum_required( VERSION 2.8 )

project( ImageRegionOverlap )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ImageRegionOverlap ImageRegionOverlap.cxx )
target_link_libraries( ImageRegionOverlap ${ITK_LIBRARIES} )

install( TARGETS ImageRegionOverlap
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES ImageRegionOverlap.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/ImageRegionOverlap
  COMPONENT Code
)

enable_testing()
add_test( NAME ImageRegionOverlapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImageRegionOverlap
    ${CMAKE_CURRENT_BINARY_DIR}/ImageRegionOverlapOutput.png
  )
