cmake_minimum_required(VERSION 3.10.2)

project(BinaryXORTwoImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(BinaryXORTwoImages Code.cxx)
target_link_libraries(BinaryXORTwoImages ${ITK_LIBRARIES})

install(TARGETS BinaryXORTwoImages
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/BinaryXORTwoImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME BinaryXORTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BinaryXORTwoImages)
