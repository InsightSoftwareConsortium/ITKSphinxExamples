cmake_minimum_required(VERSION 3.10.2)

project(AbsValueOfTwoImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(AbsValueOfTwoImages Code.cxx)
target_link_libraries(AbsValueOfTwoImages ${ITK_LIBRARIES})

install(TARGETS AbsValueOfTwoImages
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageCompare
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageCompare/AbsValueOfTwoImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME AbsValueOfTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AbsValueOfTwoImages)

