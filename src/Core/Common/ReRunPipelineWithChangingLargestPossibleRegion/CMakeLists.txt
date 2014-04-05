project( ReRunPipelineWithChangingLargestPossibleRegion )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ReRunPipelineWithChangingLargestPossibleRegion Code.cxx )
target_link_libraries( ReRunPipelineWithChangingLargestPossibleRegion ${ITK_LIBRARIES} )

install( TARGETS ReRunPipelineWithChangingLargestPossibleRegion
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/ReRunPipelineWithChangingLargestPossibleRegion
  COMPONENT Code
  )

enable_testing()
add_test( NAME ReRunPipelineWithChangingLargestPossibleRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ReRunPipelineWithChangingLargestPossibleRegion
    "mri3D_%d.mha" 0 2
  )
