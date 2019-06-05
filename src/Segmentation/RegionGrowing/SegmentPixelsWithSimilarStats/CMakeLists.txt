cmake_minimum_required(VERSION 3.10.2)

project(SegmentPixelsWithSimilarStats)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SegmentPixelsWithSimilarStats Code.cxx)
target_link_libraries(SegmentPixelsWithSimilarStats ${ITK_LIBRARIES})

install(TARGETS SegmentPixelsWithSimilarStats
  DESTINATION bin/ITKExamples/Segmentation/RegionGrowing
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/RegionGrowing/SegmentPixelsWithSimilarStats/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SegmentPixelsWithSimilarStatsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SegmentPixelsWithSimilarStats)
