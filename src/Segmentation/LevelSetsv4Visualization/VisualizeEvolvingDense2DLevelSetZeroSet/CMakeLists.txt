cmake_minimum_required(VERSION 3.8.2)

project( VisualizeEvolvingDense2DLevelSetZeroSet )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( VisualizeEvolvingDense2DLevelSetZeroSet Code.cxx )
target_link_libraries( VisualizeEvolvingDense2DLevelSetZeroSet ${ITK_LIBRARIES} )

install( TARGETS VisualizeEvolvingDense2DLevelSetZeroSet
  DESTINATION bin/ITKExamples/Segmentation/LevelSetsv4Visualization
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/LevelSetsv4Visualization/VisualizeEvolvingDense2DLevelSetZeroSet
  COMPONENT Code
  )

enable_testing()
add_test( NAME VisualizeEvolvingDense2DLevelSetZeroSetTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VisualizeEvolvingDense2DLevelSetZeroSet
    ${CMAKE_CURRENT_BINARY_DIR}/cells.png
    100
  )
set_tests_properties(
  VisualizeEvolvingDense2DLevelSetZeroSetTest
  PROPERTIES LABELS RUNS_LONG
)
