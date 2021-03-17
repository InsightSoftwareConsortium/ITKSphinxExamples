cmake_minimum_required(VERSION 3.10.2)

project(MultiphaseChanAndVeseSparseFieldLevelSetSegmentation)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MultiphaseChanAndVeseSparseFieldLevelSetSegmentation Code.cxx)
target_link_libraries(MultiphaseChanAndVeseSparseFieldLevelSetSegmentation ${ITK_LIBRARIES})

install(TARGETS MultiphaseChanAndVeseSparseFieldLevelSetSegmentation
  DESTINATION bin/ITKSphinxExamples/Nonunit/Review
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Nonunit/Review/MultiphaseChanAndVeseSparseFieldLevelSetSegmentation/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MultiphaseChanAndVeseSparseFieldLevelSetSegmentationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MultiphaseChanAndVeseSparseFieldLevelSetSegmentation)

