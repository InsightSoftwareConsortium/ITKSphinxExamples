cmake_minimum_required(VERSION 3.8.2)

project( VisualizeStaticDense2DLevelSetZeroSet )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

add_executable( VisualizeStaticDense2DLevelSetZeroSet Code.cxx )
target_link_libraries( VisualizeStaticDense2DLevelSetZeroSet ${ITK_LIBRARIES} )

install( TARGETS VisualizeStaticDense2DLevelSetZeroSet
  DESTINATION bin/ITKExamples/Segmentation/LevelSetsv4Visualization
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/LevelSetsv4Visualization/VisualizeStaticDense2DLevelSetZeroSet
  COMPONENT Code
  )

enable_testing()
add_test( NAME VisualizeStaticDense2DLevelSetZeroSetTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VisualizeStaticDense2DLevelSetZeroSet
    ${CMAKE_CURRENT_BINARY_DIR}/cells.png
    0
  )
