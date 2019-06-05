cmake_minimum_required(VERSION 3.10.2)

project(ColorLabeledRegions)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ColorLabeledRegions Code.cxx)
target_link_libraries(ColorLabeledRegions ${ITK_LIBRARIES})

install(TARGETS ColorLabeledRegions
  DESTINATION bin/ITKExamples/Filtering/ImageFusion
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFusion/ColorLabeledRegions/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ColorLabeledRegionsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ColorLabeledRegions)

