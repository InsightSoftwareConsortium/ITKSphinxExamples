cmake_minimum_required(VERSION 3.10.2)

project(ColorBoundariesOfRegions)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ColorBoundariesOfRegions Code.cxx)
target_link_libraries(ColorBoundariesOfRegions ${ITK_LIBRARIES})

install(TARGETS ColorBoundariesOfRegions
  DESTINATION bin/ITKExamples/Filtering/ImageFusion
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFusion/ColorBoundariesOfRegions/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ColorBoundariesOfRegionsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ColorBoundariesOfRegions)
