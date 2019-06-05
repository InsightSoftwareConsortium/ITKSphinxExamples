cmake_minimum_required(VERSION 3.10.2)

project(MorphologicalWatershedSegmentation)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MorphologicalWatershedSegmentation Code.cxx)
target_link_libraries(MorphologicalWatershedSegmentation ${ITK_LIBRARIES})

install(TARGETS MorphologicalWatershedSegmentation
  DESTINATION bin/ITKExamples/Segmentation/Watersheds
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Segmentation/Watersheds/MorphologicalWatershedSegmentation/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MorphologicalWatershedSegmentationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MorphologicalWatershedSegmentation)

