cmake_minimum_required(VERSION 3.10.2)

project(SetOutputPixelToMax)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SetOutputPixelToMax Code.cxx)
target_link_libraries(SetOutputPixelToMax ${ITK_LIBRARIES})

install(TARGETS SetOutputPixelToMax
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/SetOutputPixelToMax/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SetOutputPixelToMaxTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SetOutputPixelToMax)

