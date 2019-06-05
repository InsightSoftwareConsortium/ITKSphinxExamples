cmake_minimum_required(VERSION 3.10.2)

project(SinglephaseChanAndVeseSparseFieldLevelSetSegmentation2)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SinglephaseChanAndVeseSparseFieldLevelSetSegmentation2 Code.cxx)
target_link_libraries(SinglephaseChanAndVeseSparseFieldLevelSetSegmentation2 ${ITK_LIBRARIES})

install(TARGETS SinglephaseChanAndVeseSparseFieldLevelSetSegmentation2
  DESTINATION bin/ITKExamples/Nonunit/Review
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Nonunit/Review/SinglephaseChanAndVeseSparseFieldLevelSetSegmentation2/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SinglephaseChanAndVeseSparseFieldLevelSetSegmentation2Test
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SinglephaseChanAndVeseSparseFieldLevelSetSegmentation2)
