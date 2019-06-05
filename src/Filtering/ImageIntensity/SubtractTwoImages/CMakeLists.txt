cmake_minimum_required(VERSION 3.10.2)

project(SubtractTwoImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SubtractTwoImages Code.cxx)
target_link_libraries(SubtractTwoImages ${ITK_LIBRARIES})

install(TARGETS SubtractTwoImages
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/SubtractTwoImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SubtractTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SubtractTwoImages)

