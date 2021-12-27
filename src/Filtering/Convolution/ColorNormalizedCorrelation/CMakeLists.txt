cmake_minimum_required(VERSION 3.16.3)

project(ColorNormalizedCorrelation)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ColorNormalizedCorrelation Code.cxx)
target_link_libraries(ColorNormalizedCorrelation ${ITK_LIBRARIES})

install(TARGETS ColorNormalizedCorrelation
  DESTINATION bin/ITKSphinxExamples/Filtering/Convolution
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Convolution/ColorNormalizedCorrelation/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ColorNormalizedCorrelationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ColorNormalizedCorrelation)

