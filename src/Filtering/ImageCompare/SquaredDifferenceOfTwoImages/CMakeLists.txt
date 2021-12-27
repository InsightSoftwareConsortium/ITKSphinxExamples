cmake_minimum_required(VERSION 3.16.3)

project(SquaredDifferenceOfTwoImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SquaredDifferenceOfTwoImages Code.cxx)
target_link_libraries(SquaredDifferenceOfTwoImages ${ITK_LIBRARIES})

install(TARGETS SquaredDifferenceOfTwoImages
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageCompare
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageCompare/SquaredDifferenceOfTwoImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SquaredDifferenceOfTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SquaredDifferenceOfTwoImages)

