cmake_minimum_required(VERSION 3.10.2)

project(DemonstrateThresholdAlgorithms)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(DemonstrateThresholdAlgorithms Code.cxx)
target_link_libraries(DemonstrateThresholdAlgorithms ${ITK_LIBRARIES})

install(TARGETS DemonstrateThresholdAlgorithms
  DESTINATION bin/ITKExamples/Filtering/Thresholding
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Thresholding/DemonstrateThresholdAlgorithms/
  COMPONENT Code
  )


enable_testing()
add_test(NAME DemonstrateThresholdAlgorithmsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DemonstrateThresholdAlgorithms
    Yinyang.png)
