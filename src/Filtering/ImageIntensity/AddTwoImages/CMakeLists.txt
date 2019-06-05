cmake_minimum_required(VERSION 3.10.2)

project(AddTwoImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(AddTwoImages Code.cxx)
target_link_libraries(AddTwoImages ${ITK_LIBRARIES})

install(TARGETS AddTwoImages
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/AddTwoImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME AddTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AddTwoImages)
