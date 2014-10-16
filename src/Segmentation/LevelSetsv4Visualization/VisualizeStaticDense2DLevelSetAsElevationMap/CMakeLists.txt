cmake_minimum_required( VERSION 2.8.6 )

project( VisualizeStaticDense2DLevelSetAsElevationMap )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

add_executable( VisualizeStaticDense2DLevelSetAsElevationMap Code.cxx )
target_link_libraries( VisualizeStaticDense2DLevelSetAsElevationMap ${ITK_LIBRARIES} )

install( TARGETS VisualizeStaticDense2DLevelSetAsElevationMap
  DESTINATION bin/ITKExamples/Segmentation/LevelSetsv4Visualization
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/LevelSetsv4Visualization/VisualizeStaticDense2DLevelSetAsElevationMap
  COMPONENT Code
  )

enable_testing()
add_test( NAME VisualizeStaticDense2DLevelSetAsElevationMapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VisualizeStaticDense2DLevelSetAsElevationMap
    ${CMAKE_CURRENT_BINARY_DIR}/cells.png
    0
  )
