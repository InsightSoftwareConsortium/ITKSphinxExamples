cmake_minimum_required(VERSION 3.16.3)

project(SegmentWithGeodesicActiveContourLevelSet)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Segmentation/LevelSets
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Segmentation/LevelSets/SegmentWithGeodesicActiveContourLevelSet
  COMPONENT Code
  )

enable_testing()

add_test(NAME GeodesicActiveContourLeftVentricleTest
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output1.png
    81 114 5.0 1.0 -0.5 3.0 2.0 800
  )

add_test(NAME GeodesicActiveContourRightVentricleTest
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output2.png
    99 114 5.0 1.0 -0.5 3.0 2.0 800
  )

add_test(NAME GeodesicActiveContourWhiteMatterTest
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output3.png
    56 92 5.0 1.0 -0.3 2.0 10.0 800
  )

add_test(NAME GeodesicActiveContourGrayMatterTest
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output4.png
    40 90 5.0 .5 -0.3 2.0 10.0 800
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME GeodesicActiveContourLeftVentricleTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
      Output1Python.png
      81 114 5.0 1.0 -0.5 3.0 2.0 800
    )

  add_test(NAME GeodesicActiveContourRightVentricleTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
      Output2Python.png
      99 114 5.0 1.0 -0.5 3.0 2.0 800
    )

  add_test(NAME GeodesicActiveContourWhiteMatterTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
      Output3Python.png
      56 92 5.0 1.0 -0.3 2.0 10.0 800
    )

  add_test(NAME GeodesicActiveContourGrayMatterTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
      Output4Python.png
      40 90 5.0 .5 -0.3 2.0 10.0 800
    )
endif()
