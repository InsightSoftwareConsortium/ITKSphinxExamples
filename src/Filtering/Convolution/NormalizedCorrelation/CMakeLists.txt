cmake_minimum_required(VERSION 3.10.2)

project(NormalizedCorrelation)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(NormalizedCorrelation Code.cxx)
target_link_libraries(NormalizedCorrelation ${ITK_LIBRARIES})

install(TARGETS NormalizedCorrelation
  DESTINATION bin/ITKExamples/Filtering/Convolution
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Convolution/NormalizedCorrelation/
  COMPONENT Code
  )


enable_testing()
add_test(NAME NormalizedCorrelationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/NormalizedCorrelation)
