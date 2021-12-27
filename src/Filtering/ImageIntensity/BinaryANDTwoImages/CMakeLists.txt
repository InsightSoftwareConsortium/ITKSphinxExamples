cmake_minimum_required(VERSION 3.16.3)

project(BinaryANDTwoImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(BinaryANDTwoImages Code.cxx)
target_link_libraries(BinaryANDTwoImages ${ITK_LIBRARIES})

install(TARGETS BinaryANDTwoImages
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/BinaryANDTwoImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME BinaryANDTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BinaryANDTwoImages)
