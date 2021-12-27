cmake_minimum_required(VERSION 3.16.3)

project(NormalizedCorrelation)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(NormalizedCorrelation Code.cxx)
target_link_libraries(NormalizedCorrelation ${ITK_LIBRARIES})

install(TARGETS NormalizedCorrelation
  DESTINATION bin/ITKSphinxExamples/Filtering/Convolution
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Convolution/NormalizedCorrelation/
  COMPONENT Code
  )


enable_testing()
add_test(NAME NormalizedCorrelationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/NormalizedCorrelation)
