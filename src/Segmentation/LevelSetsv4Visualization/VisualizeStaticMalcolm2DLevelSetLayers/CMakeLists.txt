cmake_minimum_required( VERSION 2.8.5 )

project( VisualizeStaticMalcolm2DLevelSetLayers )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

add_executable( VisualizeStaticMalcolm2DLevelSetLayers Code.cxx )
target_link_libraries( VisualizeStaticMalcolm2DLevelSetLayers ${ITK_LIBRARIES} )

install( TARGETS VisualizeStaticMalcolm2DLevelSetLayers
  DESTINATION bin/ITKExamples/Segmentation/LevelSetsv4Visualization
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/LevelSetsv4Visualization/VisualizeStaticMalcolm2DLevelSetLayers
  COMPONENT Code
  )

enable_testing()
add_test( NAME VisualizeStaticMalcolm2DLevelSetLayersTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VisualizeStaticMalcolm2DLevelSetLayers
    ${CMAKE_CURRENT_BINARY_DIR}/cells.png
    0
  )
