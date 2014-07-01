cmake_minimum_required( VERSION 2.8.5 )
project( SegmentWithGeodesicActiveContourLevelSet )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( SegmentWithGeodesicActiveContourLevelSet Code.cxx )
target_link_libraries( SegmentWithGeodesicActiveContourLevelSet ${ITK_LIBRARIES} )

install( TARGETS SegmentWithGeodesicActiveContourLevelSet
  DESTINATION bin/ITKExamples/Segmentation/LevelSets
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/LevelSets/SegmentWithGeodesicActiveContourLevelSet
  COMPONENT Code
  )

enable_testing()

add_test(NAME GeodesicActiveContourLeftVentricleTest
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SegmentWithGeodesicActiveContourLevelSet
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output1.png
    81 114 5.0 1.0 -0.5 3.0 2.0 800
)

add_test(NAME GeodesicActiveContourRightVentricleTest
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SegmentWithGeodesicActiveContourLevelSet
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output2.png
    99 114 5.0 1.0 -0.5 3.0 2.0 800
)

add_test(NAME GeodesicActiveContourWhiteMatterTest
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SegmentWithGeodesicActiveContourLevelSet
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output3.png
    56 92 5.0 1.0 -0.3 2.0 10.0 800
)

add_test(NAME GeodesicActiveContourGrayMatterTest
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SegmentWithGeodesicActiveContourLevelSet
    ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySlice.png
    Output4.png
    40 90 5.0 .5 -0.3 2.0 10.0 800
)
