cmake_minimum_required(VERSION 3.10.2)

project(SinglephaseChanAndVeseSparseFieldLevelSetSegmentation)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SinglephaseChanAndVeseSparseFieldLevelSetSegmentation Code.cxx)
target_link_libraries(SinglephaseChanAndVeseSparseFieldLevelSetSegmentation ${ITK_LIBRARIES})

install(TARGETS SinglephaseChanAndVeseSparseFieldLevelSetSegmentation
  DESTINATION bin/ITKExamples/Nonunit/Review
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Nonunit/Review/SinglephaseChanAndVeseSparseFieldLevelSetSegmentation/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SinglephaseChanAndVeseSparseFieldLevelSetSegmentationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SinglephaseChanAndVeseSparseFieldLevelSetSegmentation)
