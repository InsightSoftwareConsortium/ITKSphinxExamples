cmake_minimum_required(VERSION 3.10.2)

project(InvertImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(InvertImage Code.cxx)
target_link_libraries(InvertImage ${ITK_LIBRARIES})

install(TARGETS InvertImage
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/InvertImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME InvertImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/InvertImage)

