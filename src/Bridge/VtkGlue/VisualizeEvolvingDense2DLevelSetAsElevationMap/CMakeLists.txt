cmake_minimum_required(VERSION 3.16.3)

project(VisualizeEvolvingDense2DLevelSetAsElevationMap)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Bridge/VtkGlue
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Bridge/VtkGlue/VisualizeEvolvingDense2DLevelSetAsElevationMap
  COMPONENT Code
  )

enable_testing()
add_test(NAME VisualizeEvolvingDense2DLevelSetAsElevationMapTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/cells.png
    100
  )
set_tests_properties(
  VisualizeEvolvingDense2DLevelSetAsElevationMapTest
  PROPERTIES LABELS RUNS_LONG
)
