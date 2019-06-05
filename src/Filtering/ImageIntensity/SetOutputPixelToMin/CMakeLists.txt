cmake_minimum_required(VERSION 3.10.2)

project(SetOutputPixelToMin)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SetOutputPixelToMin Code.cxx)
target_link_libraries(SetOutputPixelToMin ${ITK_LIBRARIES})

install(TARGETS SetOutputPixelToMin
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/SetOutputPixelToMin/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SetOutputPixelToMinTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SetOutputPixelToMin)
